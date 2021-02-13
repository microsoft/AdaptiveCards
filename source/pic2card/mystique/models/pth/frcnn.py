import torch
from detecto.core import Model
from detecto.core import DataLoader


class CustomModel(Model):

    def __init__(self, classes=None, device=None, log_writer=None):
        self.log_writer = log_writer
        super(CustomModel, self).__init__(classes, device)

    def get_model_name(self, prefix="frcnn"):
        """
        Generate name based on the parameters given.
        """
        pass

    def fit(self, dataset, val_dataset=None, epochs=10,
            learning_rate=0.00002, momentum=0.9,
            weight_decay=0.00005, gamma=0.1, lr_step_size=3, verbose=False):

        # If doing custom training, the given images will most likely be
        # normalized. This should fix the issue of poor performance on
        # default classes when normalizing, so resume normalizing. TODO
        if epochs > 0:
            self._disable_normalize = False

        # Convert dataset to data loader if not already
        if not isinstance(dataset, DataLoader):
            dataset = DataLoader(dataset, shuffle=True)

        if val_dataset is not None and not isinstance(val_dataset, DataLoader):
            val_dataset = DataLoader(val_dataset)

        losses = []
        # Get parameters that have grad turned on (i.e. parameters that should
        # be trained)
        parameters = [p for p in self._model.parameters() if p.requires_grad]
        # Create an optimizer that uses SGD (stochastic gradient descent)
        # to train the parameters
        optimizer = torch.optim.SGD(parameters,
                                    lr=learning_rate,
                                    momentum=momentum)
        # Create a learning rate scheduler that decreases learning rate
        # by gamma every lr_step_size epochs
        # lr_scheduler = torch.optim.lr_scheduler.StepLR(
        #     optimizer, step_size=lr_step_size, gamma=gamma
        # )

        lr_scheduler = torch.optim.lr_scheduler.MultiStepLR(
            optimizer, milestones=[10, 20], gamma=gamma
        )

        # Train on the entire dataset for the specified number of
        # times (epochs)
        for epoch in range(epochs):
            if verbose:
                print('Epoch {} of {}'.format(epoch + 1, epochs))

            # Training step
            avg_train_loss = 0.
            self._model.train()
            for images, targets in dataset:
                self._convert_to_int_labels(targets)
                images, targets = self._to_device(images, targets)

                # Calculate the model's loss (i.e. how well it does on the
                # current image and target, with a lower loss being better)
                loss_dict = self._model(images, targets)
                total_loss = sum(loss for loss in loss_dict.values())
                avg_train_loss += total_loss
                # print(f"Batch: {len(images)}, loss: {total_loss}")
                # Zero any old/existing gradients on the model's parameters
                optimizer.zero_grad()
                # Compute gradients for each parameter based on the current
                # loss calculation
                total_loss.backward()
                # Update model parameters from gradients:
                # param -= learning_rate * param.grad
                optimizer.step()

            avg_train_loss /= len(dataset)

            if verbose:
                print('Train Loss: {}'.format(avg_train_loss))
                self.log_writer.add_scalar("Loss/train", avg_train_loss, epoch)

            # Validation step
            if val_dataset is not None:
                avg_loss = 0
                with torch.no_grad():
                    for images, targets in dataset:
                        self._convert_to_int_labels(targets)
                        images, targets = self._to_device(images, targets)
                        loss_dict = self._model(images, targets)
                        total_loss = sum(loss for loss in loss_dict.values())
                        avg_loss += total_loss.item()

                avg_loss /= len(val_dataset.dataset)
                losses.append(avg_loss)

                if verbose:
                    print('Loss: {}'.format(avg_loss))
                    self.log_writer.add_scalar("Loss/val", avg_loss, epoch)

            # Update the learning rate every few epochs
            lr_scheduler.step()

        if len(losses) > 0:
            return losses

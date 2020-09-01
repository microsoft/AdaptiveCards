"""This module converts the labelled traning and testing xmls generated
   from the labelImg tool to object:boundary:image mapped csv.
"""
import click

from mystique.utils import xml_to_csv


@click.command()
@click.option("--labelmg-dir", required=True,
              help="path to the xml and png file from labelmg")
@click.option("--csv-out-file", required=True,
              help="Export the bbox in csv format")
def main(labelmg_dir, csv_out_file):
    """
    Writes the mapped object boundaries:image csv rows into the
    data folder
    """
    xml_df = xml_to_csv(labelmg_dir)
    xml_df.to_csv(csv_out_file, index=False)
    print("Successfully converted xml to csv.")


if __name__ == "__main__":
    main()

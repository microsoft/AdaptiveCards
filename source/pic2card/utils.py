
from contextlib import contextmanager
import time


@contextmanager
def timeit(name="code-block"):
    """
    Execute the codeblock and measure the time.

    >> with timeit('name') as f:
    >>     # Your code block
    """
    try:
        start = time.time()
        yield
    finally:
        # Execution is over.
        end = time.time() - start
        print(f"Execution block: {name} finishes in : {end} sec.")

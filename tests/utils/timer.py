import time

class Timer:
    def __init__(self):
        self.start_time = None
        self.end_time = None

    def start(self):
        self.start_time = time.perf_counter()

    def stop(self):
        self.end_time = time.perf_counter()

    def show(self):
        if self.start is None or self.end_time is None:
            return 0.0
        
        print(f"\nExecution time: {self.end_time - self.start_time:.3f}s")
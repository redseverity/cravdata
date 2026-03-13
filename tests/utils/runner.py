import subprocess

def run(args: list):
    return subprocess.run(
        args,
        capture_output=True,
        text=True,
        timeout=3
    )

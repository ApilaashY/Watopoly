#!/usr/bin/env python3
"""Collect all .cc files from this project into a submit/ folder.

Behavior:
- Walks the project tree from the script's directory.
- Copies every .cc file into submit/ while preserving relative paths.
- Skips the submit/ directory itself to avoid re-copying.
"""

from pathlib import Path
import shutil


def main() -> None:
    root = Path(__file__).resolve().parent
    submit_dir = root / "submit"
    submit_dir.mkdir(exist_ok=True)

    # Remove any existing content so submit/ ends up flat on every run.
    for item in submit_dir.iterdir():
        if item.is_dir():
            shutil.rmtree(item)
        else:
            item.unlink()

    copied = 0
    for cc_file in root.rglob("*.cc"):
        # Avoid traversing files already inside submit/
        if submit_dir in cc_file.parents:
            continue

        # Flatten output: place all .cc files directly in submit/
        target = submit_dir / cc_file.name

        # If names collide, append a numeric suffix to keep all files.
        if target.exists():
            stem = cc_file.stem
            suffix = cc_file.suffix
            counter = 1
            while True:
                candidate = submit_dir / f"{stem}_{counter}{suffix}"
                if not candidate.exists():
                    target = candidate
                    break
                counter += 1

        shutil.copy2(cc_file, target)
        copied += 1

    # Copy order.txt into submit/ with flattened filenames (no directory prefixes).
    order_file = root / "order.txt"
    if order_file.exists():
        flattened_lines = []
        for line in order_file.read_text(encoding="utf-8").splitlines():
            entry = line.strip()
            if entry == "":
                flattened_lines.append("")
            else:
                flattened_lines.append(Path(entry).name)

        (submit_dir / "order.txt").write_text(
            "\n".join(flattened_lines) + "\n",
            encoding="utf-8",
        )

    print(f"Copied {copied} .cc files into: {submit_dir}")


if __name__ == "__main__":
    main()

    shutil.copyfile("syslibs.txt", "submit/syslibs.txt")

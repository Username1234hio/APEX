# Fix: Move project out of a directory path containing spaces

GNU Make (used internally by Verilator) cannot handle paths with spaces.
Your current path has spaces:
  /mnt/d/Aaditya Projects/APEX Chip/APEX/APEX1_final/apex1/
                  ^^^^^^^       ^^^^
These spaces are the only problem. The RTL and scripts are all fine.

## Option A — Move the project (recommended, 30 seconds)

Open a terminal and run:

    # Windows/WSL — move to a no-space path on your D: drive
    mv "/mnt/d/Aaditya Projects/APEX Chip/APEX/APEX1_final" /mnt/d/apex1_project
    cd /mnt/d/apex1_project/apex1
    ./compile_array.sh

Or pick any path with no spaces:
    /mnt/d/apex1/
    /mnt/d/projects/apex1/
    ~/apex1/

## Option B — Use a symlink (no file copying needed)

    ln -s "/mnt/d/Aaditya Projects/APEX Chip/APEX/APEX1_final/apex1" /mnt/d/apex1
    cd /mnt/d/apex1
    ./compile_array.sh

The symlink path has no spaces so Make is happy, but the files stay where they are.

## Option C — Build into /tmp (output only, not the source)

The source path is fine — only the OUTPUT directory (obj_dir_array_8) must be
in a no-space path. The compile scripts already write to a relative path
(obj_dir_array_8 inside the project dir) so Option A or B is easiest.

# Chessboard Firmware

Firmware for a smart chessboard built on **nRF52840** and **Zephyr RTOS**.

This project was developed as an engineering thesis by **Seweryn Malczewski** and **Dominika Lasa**.

## Educational Note

This was our first large embedded systems project.
It is published as an educational/portfolio project, and it most likely still contains bugs and areas that need improvement.

## What This Project Does

The system handles a physical chessboard and synchronizes game state using board-square sensor readings.

Key features:

- 64-square piece state detection (pick-up / put-down),
- full chess rules handling (including special cases),
- per-square LED highlighting,
- two independent player displays (white/black) with an LVGL-based UI,
- firmware image flow prepared for MCUboot updates.

## Demo

Project demo (presentation + embedded video showing the system in action):

- **Canva presentation (PL):** https://www.canva.com/design/DAGd6gJVaPo/vVfK3YDnZuc7xg0F_5g1jA/view?utm_content=DAGd6gJVaPo&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=h2b56bc22a3

## Tech Stack

- **nRF Connect SDK 2.6.1** (manifest `west.yml`)
- **Zephyr RTOS**
- **C / C++14**
- **LVGL**
- **CMake + West**
- chess logic unit tests: **Catch2** (test build target)

## Repository Structure

- `app/` - main application (UI, integration logic, event handling)
- `lib/chess_logic/` - chess rules library + unit tests
- `drivers/sensor/tiles/` - custom Zephyr sensor driver for chessboard tile modules
- `boards/arm/chessboard/` - custom board definition and DeviceTree
- `scripts/` - helper scripts (init, build, tests, coverage)

## Quick Start

### Requirements

- installed nRF Connect SDK toolchain and `west`,
- Python 3,
- a programmer/debug probe compatible with `west flash` (for example J-Link).

### 1. Initialize dependencies

```bash
./scripts/init.sh
```

This script pulls dependencies using `west update`.

### 2. Build firmware

```bash
./scripts/build.sh
```

### 3. Flash to the board

```bash
west flash
```

## Useful Commands

```bash
# Build debug
./scripts/build-debug.sh

# Kconfig menu
./scripts/menuconfig.sh

# Build chess-logic tests
./scripts/build-test.sh

# Run tests
./scripts/test.sh

# JUnit XML report
./scripts/test-xml.sh

# Coverage (after build-test)
./scripts/coverage.sh
```

## License

This project code is released under the **Apache-2.0** license (see `LICENSE`).

Note: the firmware depends on components fetched through nRF Connect SDK, which remain under their original licenses. Details and restrictions (including Nordic components under `LicenseRef-Nordic-5-Clause`) are documented in `THIRD_PARTY_LICENSES.md`.

## Authors

- Seweryn Malczewski
- Dominika Lasa

## Acknowledgments

This project was made possible thanks to support from **JLCPCB**, which provided financial support to our student group to help deliver such an ambitious project.

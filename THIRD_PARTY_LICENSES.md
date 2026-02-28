# Third-Party Licenses

This project uses third-party components fetched via `west update` (as defined in `west.yml`).

## 1) Zephyr RTOS

- Source: `external/zephyr`
- License: **Apache License 2.0**
- License file: `external/zephyr/LICENSE`

## 2) nRF Connect SDK (Nordic)

- Source: `external/nrf`
- Licensing model: mixed (multiple components under different licenses)
- Example license used by some Nordic components: **LicenseRef-Nordic-5-Clause**
- Reference file: `external/nrf/LICENSE`

### Important restrictions for LicenseRef-Nordic-5-Clause

In particular, this license includes restrictions such as:
- software use only with Nordic Semiconductor integrated circuits,
- additional conditions for binary distribution.

## 3) nrfxlib

- Source: `external/nrfxlib`
- Licensing model: component-dependent
- Examples:
  - `external/nrfxlib/LICENSE`
  - `external/nrfxlib/mpsl/license.txt`

## Scope of This Repository License

The root `LICENSE` file applies to the original code in this repository.
Code and libraries provided by third-party dependencies remain under their original licenses and terms.

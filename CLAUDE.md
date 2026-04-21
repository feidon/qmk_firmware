# QMK Firmware — feidon's personal fork

Personal fork of [QMK](https://github.com/qmk/qmk_firmware) tracking upstream while carrying custom keymaps. Official docs: https://docs.qmk.fm/

## Remotes and branches

- `origin` → `https://github.com/feidon/qmk_firmware` (personal fork)
- `upstream` → `https://github.com/qmk/qmk_firmware` (real QMK repo)
- `master` → tracks upstream QMK master (never commit to it directly)
- `feidon` → working branch with personal keymaps; rebased onto `origin/master` periodically

**Never push PRs upstream.** Work stays on the `feidon` branch in the personal fork.

## Personal keymaps

Two keyboards with `feidon` keymaps:

| Keyboard | Path | Pointing device |
|---|---|---|
| Bastardkb Charybdis 3x5 | `keyboards/bastardkb/charybdis/3x5/keymaps/feidon/` | PMW3360 trackball |
| Corne (crkbd) | `keyboards/crkbd/keymaps/feidon/` | Cirque Pinnacle I2C trackpad |

Both are split keyboards with `EE_HANDS`, TAP_DANCE, COMBO enabled.

### Charybdis 3x5 layout note

The `feidon` keymap uses a **36-key LAYOUT** (4 thumb keys per side via matrix `[3,4]`/`[7,3]`/`[7,4]`), which is a custom divergence from upstream's 35-key default (3 thumb keys). `keyboards/bastardkb/charybdis/3x5/info.json` carries this customization — do not accept upstream's LAYOUT shape during rebase or the keymap will fail to compile (argument-count mismatch in `LAYOUT(...)` calls).

### splinky_3 controller removed upstream

Upstream removed `keyboards/bastardkb/charybdis/3x5/v2/splinky_3/` in PR #25488 (commit `56ad3a5f43`, July 2025). For RP2040 controllers, build against `elitec` + converter instead of restoring the `v2/` directory:

```
qmk compile -kb bastardkb/charybdis/3x5/elitec -km feidon -e CONVERT_TO=rp2040_ce
```

(Or `blackpill` for STM32.) See the [Converters doc](https://docs.qmk.fm/#/feature_converters) for the correct `CONVERT_TO` target matching the physical controller.

## Common commands

```bash
# Build (examples — adjust -kb to your actual controller)
qmk compile -kb bastardkb/charybdis/3x5/elitec -km feidon -e CONVERT_TO=rp2040_ce
qmk compile -kb crkbd/rev1 -km feidon

# Flash
qmk flash -kb <keyboard> -km feidon

# Format C code (QMK standard: clang-format)
qmk format-c
```

## Rebasing onto upstream

Workflow when upstream master moves:

```bash
git fetch origin master
git rebase origin/master
# resolve conflicts, then:
git push --force-with-lease origin feidon
```

**During rebase, watch for:**

- **False rename conflicts.** Git's rename detection often matches deleted files (e.g. `charybdis/3x5/v2/splinky_3/config.h`) to unrelated new keyboards (e.g. `mzmkb/slimdash/rev1/config.h`) based on boilerplate similarity. When you see a conflict between totally unrelated keyboards, it's almost always this — take `--ours` (HEAD/upstream) and move the intended change to your keymap-level `config.h` instead.
- **Commits that become empty** after conflict resolution are auto-dropped. If the commit only edited an upstream-deleted file, its change must be re-applied in your keymap dir.
- **Submodules** (`lib/chibios`, `lib/chibios-contrib`, `lib/pico-sdk`) show "new commits" during rebase when the `feidon` tip has older submodule pointers than `origin/master`. This resolves itself as long as no feidon commit touches the submodule pointers — verify with `git log --oneline master..feidon -- lib/chibios lib/chibios-contrib lib/pico-sdk`.

## Overriding board-level defines from a keymap

QMK's `config.h` include chain cascades from most-specific to least (keymap > keyboard-revision > keyboard > common). To override an already-defined macro (not just set an undefined one), use `#undef` then `#define`:

```c
// keyboards/bastardkb/charybdis/3x5/keymaps/feidon/config.h
#undef ROTATIONAL_TRANSFORM_ANGLE
#define ROTATIONAL_TRANSFORM_ANGLE -20
```

Without `#undef`, the compiler emits a redefinition warning and may keep the original value depending on ordering. This is the clean way to diverge from upstream board defaults without editing files outside your keymap directory.

## Do NOT

- Commit directly to `master`
- Create PRs to `upstream` (qmk/qmk_firmware)
- Edit files outside `keymaps/feidon/` or your personal keyboard config when diverging from upstream — push the override into the keymap dir instead
- Modify submodule pointers (`lib/chibios`, `lib/chibios-contrib`, `lib/pico-sdk`) in feidon commits; let them track upstream master

## Useful docs

- Main docs: https://docs.qmk.fm/
- Keymap overview: https://docs.qmk.fm/#/keymap
- Config options: https://docs.qmk.fm/#/config_options
- Pointing devices: https://docs.qmk.fm/#/feature_pointing_device
- Converters (e.g. RP2040 CE): https://docs.qmk.fm/#/feature_converters
- `qmk` CLI reference: https://docs.qmk.fm/#/cli_commands

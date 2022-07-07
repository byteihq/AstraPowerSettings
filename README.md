## Build
```sh
cmake -H. -B_build
```
```sh
cmake --build B_build
```
**OR**
```sh
./build.sh
```
## Install
```sh
cmake -H. -B_build
```
```sh
sudo cmake --build _build --target install
```
## Params
### User
- **user** - User name (u - by default)
### Tlp
- **tlp_path** - Path to tlp config (./Misc/tlp - by default)
### Tests
- **tests_enabled** - Enable testing power supply (disabled - by default)
- **tests_duration** - Test duration (5 min - by default; **only works when tests_enabled=true**)

## Example
```sh
sudo ./AstraPowerSettings --tests_enabled=true --tests_duration=10
```

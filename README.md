# event_system

Simple publisher/subscriber system in modern C++.

## Building

```sh
# Clone the repository:
git clone https://github.com/loganfin/event_system.git

# Navigate into the new directory:
cd event_system

# Configure the project in a new directory called "build":
cmake -B build

# Build the project that's been configured in the "build" directory:
cmake --build build
```

## Example

```sh
$ ./build/event_system
> bob move
bob is moving one space...
> charles move
Invalid character name.
> bob swing
Unknown command.
>
```

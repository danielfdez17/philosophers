# philosophers 42 Madrid
This objective of the project is to simulate the dinning philosophers problem with threads and mutexes

## Installation
- Clone the repo
```bash
git clone https://github.com/danielfdez17/philosophers.git
cd philosophers/philo
```
## Build
If you have make installed in your system, justbBuild the project with make. Otherwise, you will need to install it.
```bash
make
```

## Usage
It is necessary to indicate the first four params. On the other hand, the last one is optional.
```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [n_eat_per_filo]
```
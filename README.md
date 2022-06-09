<p align="center">
  <a href="https://42lyon.fr/">
    <img src="https://github.com/llecoq/philosophers/blob/main/assets/final%20grade.png" alt="philosophers" width=200 height=170>
  </a>

  <h2 align="center">philosophers</h2>

  <p align="center">
    In this project, you will learn the basics of threading a process.
    <br>  
    You will see how to create threads and you will discover mutexes.
    <br>
    <br>
    /!\ SUBJECT LINKED MAY DIFFER FROM THE ONE USED FOR THIS PROGRAM /!\
    <br>
    <a href="https://github.com/llecoq/philosophers/blob/master/assets/en.subject.pdf">English Subject </a>
  </p>
</p>


## Table of contents

- [Quick start](#quick-start)
- [What's included](#whats-included)
- [Creators](#creators)


## Quick start

Philosopers is a fun project !

Compile :
```
make
```

Run program :
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

```number_of_philosophers:```

The number of philosophers and also the number
of forks.

<br>
<br>

```time_to_die (in milliseconds):```

If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

<br>
<br> 

```time_to_eat (in milliseconds):```

The time it takes for a philosopher to eat.

<br>
<br> 

```time_to_sleep (in milliseconds):```

The time a philosopher will spend sleeping.

<br>
<br> 

```number_of_times_each_philosopher_must_eat (optional argument):```

If all philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a hilosopher dies.

## What's included

```
philosophers
├── Makefile
├── README.md
├── assets
│   ├── en.subject.pdf
│   └── final grade.png
├── includes
│   ├── enum.h
│   └── philosophers.h
├── philo
└── srcs
    ├── execution
    │   ├── actions.c
    │   └── executor.c
    ├── main.c
    ├── parsing
    │   └── parser.c
    └── utils
        ├── error.c
        ├── ft_atoi.c
        ├── life_vs_death.c
        ├── mutex.c
        ├── print_action.c
        ├── sleep.c
        └── time.c
```

## Creators

**llecoq**

- <https://github.com/llecoq>

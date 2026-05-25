# Philosophers
Grade achieved: 121% ✅
>[!NOTE]
>Small bug was fixed right after the evaluation  
## ℹ️Description
**Subject: Concurrent Programming**
- Using threads, mutexes, semaphores and forks, I solve the well-known "Dining Philosophers Problem"
- Philosophers must eat, sleep and think. If a philosopher does not eat for long, it dies.
- There are as many forks as philosophers, but philosophers need two forks🍴 to eat.
- The goal is to optimise a routine which minimises a chance of philosophers "dying"
  
### Mandatory Section:
- Using only threads and mutexes, I create a routine where each philosopher is represented by a thread, and forks🍴 are mutexes

### 🏆Bonus Section:
- Using forks() and semaphores, I create a routine where each philosopher is represented by a fork() and forks🍴 are semaphores


## 🛠️ Usage
```bash
cd philo
make
./philo <time to die> <time to eat> <time to sleep> (optional) <times each philo must eat>
(e.g.) ./philo 800 200 200 10
```

## 👥 Author
Matilda Tice (42: mtice, Github: mstice)  
<sub>Cover image by [Ayogun](https://github.com/ayogun/42-project-badges)</sub>

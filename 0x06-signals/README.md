# 0x06. C - Signals

## Resources:books:
Read or watch:
* [Signals](https://intranet.hbtn.io/rltoken/ukPkQ6GGQY_8Q5f-dBALdQ)
* [Asynchrony](https://intranet.hbtn.io/rltoken/tOCa7cR0tnL9U9S61pfCmw)
* [Signal sets](https://intranet.hbtn.io/rltoken/khUw0UIowrZpgxSmc1brTA)

---
## Learning Objectives:bulb:
What you should learn from this project:

* What is a signal
* Why do they exist
* When are they delivered and by whom
* What are the default actions of signals
* How to set up a handler for a signal
* How to send signals
* What signals can’t be caught

---

### [0. Handle signal](./0-handle_signal.c)
* Write a function that set a handler for the signal SIGINT


### [1. Current handler - signal](./1-current_handler_signal.c)
* Write a function that retrieves the current handler of the signal SIGINT


### [2. Gotta catch them all](./2-handle_sigaction.c)
* Write a function that set a handler for the signal SIGINT


### [3. Current handler - sigaction](./3-current_handler_sigaction.c)
* Write a function that retrieves the current handler of the signal SIGINT


### [4. Who said that?!](./4-trace_signal_sender.c)
* Write a function that defines a handler for the signal SIGQUIT (Control-\ in a shell)


### [5. Description](./5-signal_describe.c)
* Write a program that prints a description of a given signal


### [6. Catch a single time](./6-suspend.c)
* Write a program that sets a handler for the signal SIGINT, and exits right after the signal is received and handled


### [7. Sending a signal](./7-signal_send.c)
* Write a program that sends the signal SIGINT to a process, given its PID


### [8. Sending a signal in a shell](./8-signal_send.sh)
* Write a sh script that sends the signal SIGQUIT to a process, given its PID


### [9. Catch with sh](./9-handle_signal.sh)
* Write a sh script that set a handler for the signals SIGABRT, SIGIO and SIGTERM


### [10. Does it exist?](./10-pid_exist.c)
* Write a function that tests if a process exists, given its PID


---

## Author
* **Arturo Victoria Rincon** - [arvicrin](https://github.com/arvicrin)
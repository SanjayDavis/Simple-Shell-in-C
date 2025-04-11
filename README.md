<<<<<<< HEAD
# Simple-Shell-in-C-with-Custom-Prompt-and-Command-Execution
This project implements a basic shell (command-line interpreter) in C that allows users to enter and execute Unix commands interactively. The shell is built using standard C libraries and provides simple yet useful features for parsing and executing user commands.
=======
# 🔧 Simple Shell in C

A lightweight Unix-like shell implemented in C that supports basic command execution, dynamic prompt customization, and safe input handling using standard libraries.

---

## 📌 Features

- ✅ **Custom Shell Prompt**  
  Change the prompt at runtime using the command:
  ```bash
  start = <your_prompt>
  ```
  Example:
  ```bash
  start = "myShell"
  ```
  Output:
  ```
  myShell:
  ```

- ✅ **Command Execution**  
  Executes standard Linux/Unix commands using `fork()` and `execvp()`.  
  Example:
  ```
  >: ls -l
  ```

- ✅ **Safe Input Handling**  
  Uses `fgets()` to prevent buffer overflow.

---

## ⚙️ How It Works

1. **Displays the shell prompt** (`>:` by default).
2. **Waits for user input.**
3. **Parses input** using `strtok()` to extract command and arguments.
4. **Executes the command** using a child process (`fork` + `execvp`).
5. **Repeats** until manually exited (e.g., with `Ctrl+C` or `Ctrl+D`).

---

## 💪 Technologies Used

- C Programming Language
- POSIX System Calls (`fork()`, `execvp()`, `wait()`)
- Standard C Libraries (`stdio.h`, `stdlib.h`, `string.h`, `unistd.h`)

---

## 📁 File Structure

```
.
├── shell.c        # Main C source file
└── README.md      # Project documentation
```

---

## 🚀 Compilation

To compile the program:

```bash
gcc shell.c -o shell
```

To run the shell:

```bash
./shell
```

---

## 🧪 Sample Usage

```bash
>: ls
file1.txt  file2.c  folder/

>: start = myShell
myShell: pwd
/home/user/myShell

myShell: echo Hello World
Hello World
```

---

## ❗ Notes

- Arrow keys will not work as expected (e.g., no cursor movement/history) because this shell does not use advanced input handling (like `readline`).
- To exit the shell, use `Ctrl+C` or `Ctrl+D` or type `exit`.

---

## 📄 License

This project is released under the [MIT License](LICENSE).

---

## 🙌 Acknowledgements

Thanks to the creators of Unix and the GNU tools for inspiring this project.

>>>>>>> 6288086 (first commit)

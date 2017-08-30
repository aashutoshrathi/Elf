# Elf
OS Lab Mini Project

### Instructions

* First of all fork this repository using <a class="github-button" href="https://github.com/aashutoshrathi/Elf/fork" data-size="small" data-show-count="true" aria-label="Fork aashutoshrathi/Elf on GitHub">Fork</a>
* Clone your forked repo using 
```md
git clone https://github.com/Your-Username/Elf.git
```

* Change Directory to Elf, using 
```md
cd Elf
```

* Add remote branch using 
```md
git remote add upstream https://github.com/aashutoshrathi/Elf.git
```

* Do your work in a seprate branch never make a function in master itself.
* You just need to implement function part in [Basic Structure](#bs) in a file named same as function.
* Create a new branch using 
```md
git branch -b "Branch-Name"
```

* When completed push your work, and Send a Pull-Request.
* Try maintaing code quality, indentation and standards.
* After review it will be added to Project and merged with our master function.

<a name="bs"></a>
### Basic Structure

```c
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int function(void); // Declaration

int main() {
	char arg[1024];
	while(strcmp(arg,"exit") != 0){	
		printf("myshell$ "); // As we are making bash.
		scanf("%s", arg);
		switch(arg[0]) {
			case 'TriggerKey':
			function();
		}
	}
	exit(0);
}

int function() {
	/*
        Your implementation here...
    */
}
```


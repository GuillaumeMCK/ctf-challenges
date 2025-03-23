# Solution

```bash
cat ./pass
```

```bash
â  rev_spookypass cat pass
ELF>   ||ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½888@xxxDDSï¿½d888@Pï¿½dï¿½ï¿½ï¿½$$Qï¿½dRï¿½dï¿½ï¿½ï¿½00/lib64/ld-linux-x86-64.so.20GNUGNU!wrï¿½&ï¿½ÖlqTGNU

                                                                                                  gUa#
DKR  5"fgetsstdinputs__stack_chk_fail__libc_start_main__cxa_finalizestrchrprintfstrcmplibc.so.6GLIBC_2.4GLIBC_2.2.5GLIBC_2.34_ITM_deregisterTMCloneTable__gmon_start___ITM_recuiterTMmy0HH@?ï¿½ï¿½eYii   ï¿½
ï¿½
 ï¿½            5ï¿½H)Hï¿½ï¿½HHï¿½ï¿½tH.H
pHï¿½cHï¿½t/]ï¿½.=ï¿½H                                [HÇ¸ï¿½Hï¿½H  /H9tHï¿½H
Hï¿½/H5ï¿½%ï¿½ï¿½ï¿½Hï¿½f.ï¿½hï¿½%/hï¿½%/hï¿½%/hï¿½%/hï¿½ï¿½1ï¿½ï¿½Hï¿½ï¿½P2Hï¿½RH  /ï¿½. =0H
HHHt          @ï¿½ï¿½UHï¿½ï¿½dH%(HE1HÇPHÇXHÇZHÇbH          H
Hï¿½6BHï¿½ï¿½ÇDï¿½
DHP
D     ï¿½Hï¿½_HUdH+%(tï¿½ï¿½ï¿½Hï¿½Hï¿½ï¿½Welcome to the SPOOKIEST party of the year.
Before we let you in, you'll need to give us the password: s3cr3t_p455_f0r_gh05t5_4nd_gh0ul5
Welcome inside!
You're not a real ghost; clear off! Dï¿½Tï¿½<ï¿½|zRx
                                                J
^                                                ?;*3$"\)ï¿½cAC
0Y
ï¿½o ï¿½
ï¿½
 ï¿½oï¿½oï¿½oï¿½6FVfvH@HTB{un0bfu5c4t3d_5tr1ng5}
GCC: (GNU) 14.2.1 20240805
GCC: (GNU) 14.2.1 20240910
ï¿½ï¿½ï¿½$ï¿½:W  @@s
0ï¿½61ï¿½   ï¿½5%
```

### Why does the flag appear in the output?


The flag `HTB{un0bfu5c4t3d_5tr1ng5}` appears because `cat` read files a stream of bytes and displays their content directly to standard output. Because of this, any readable text within the file, including the flag, is displayed as-is without any modification or obfuscation

---

## Static Analysis

The relevant part of the code:

```c
int main(void)
{
  int rightPwd;
  char *charAt10;
  long in_FS_OFFSET;
  uint i;
  undefined8 flag;
  undefined2 local_b0;
  undefined6 uStack_ae;
  undefined2 uStack_a8;
  undefined8 local_a6;
  char password [136];
  long local_10;

  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  flag = 0;
  local_b0 = 0;
  uStack_ae = 0;
  uStack_a8 = 0;
  local_a6 = 0;
  puts("Welcome to the \x1b[1;3mSPOOKIEST\x1b[0m party of the year.");
  printf("Before we let you in, you\'ll need to give us the password: ");
  fgets(password,0x80,stdin);
  charAt10 = strchr(password,10);
  if (charAt10 != (char *)0x0) {
    *charAt10 = '\0';
  }
  rightPwd = strcmp(password,"s3cr3t_p455_f0r_gh05t5_4nd_gh0ul5");
  if (rightPwd == 0) {
    puts("Welcome inside!");
    for (i = 0; i < 26; i = i + 1) {
      *(char *)((long)&flag + (long)(int)i) = (char)*(undefined4 *)(parts + (long)(int)i * 4);
    }
    puts((char *)&flag);
  }
  else {
    puts("You\'re not a real ghost; clear off!");
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}
```

### Explanation

1. **Takes User Input:**

   - The program prompts the user to enter a password.

2. **Removes Newline Character:**

   - If the input contains a newline (`\n`), it replaces it with a null terminator (`\0`).

3. **Compares Password:**

   - It checks if the input matches `"s3cr3t_p455_f0r_gh05t5_4nd_gh0ul5"`.

4. **Grants Access if Correct:**
   - If the password matches, it prints `"Welcome inside!"`.
   - It then reconstructs a hidden message from an array (`parts`) by copying 26 bytes into `flag`.
   - The message (flag) is then printed.

---

## Obfuscated String (`parts`)

The data stored in `parts`:

```hex
48 00 00 00 54 00 00 00 42 00 00 00 7b 00 00 00 75 00 00 00 6e 00 00 00 30 00 00 00 62 00 00 00 66 00 00 00 75 00 00 00 35 00 00 00 63 00 00 00 34 00 00 00 74 00 00 00 33 00 00 00 64 00 00 00 5f 00 00 00 35 00 00 00 74 00 00 00 72 00 00 00 31 00 00 00 6e 00 00 00 67 00 00 00 35 00 00 00 7d 00 00 00 00 00 00 00
```

Interpreted as ASCII:

```ascii
H...T...B...{...u...n...0...b...f...u...5...c...4...t...3...d..._...5...t...r...1...n...g...5...}.......
```

### How it's extracted

The loop:

```c
for (i = 0; i < 26; i = i + 1) {
  *(char *)((long)&flag + (long)(int)i) = (char)*(undefined4 *)(parts + (long)(int)i * 4);
}
```

- Reads 26 characters from `parts`.
- Extracts one character per 4 bytes (removing unnecessary padding).
- Stores them in `flag`, which is then printed.

### Result

The flag appears as:

```text
HTB{un0bfu5c4t3d_5tr1ng5}
```

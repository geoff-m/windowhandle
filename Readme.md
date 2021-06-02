# windowhandle
A Windows debugging tool that lists the handles and window text of all a process's windows.

## Building
Use `cmake`.

## Usage
Provide a single command line argument, the process ID of the process whose windows will be enumerated.

## Example
```
> windowhandle 31604
Found 6 windows for process 31604.
Handle                  Text
00000000001A1510        G
00000000001F1414        Default IME
00000000003212F6
00000000003512B6        MSCTFIME UI
00000000003517AC        Default IME
0000000000670F82        Untitled - Paint
```

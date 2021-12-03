### Saving the code

**Description**:
The User can save the current working window or can compile his code to an object file.

**Actors**:

- The User (Programmer)

**Preconditions**:
The application is running and a file is open.

**Postconditions**:
Code is either saved or exported to an object file.

**Main scenario**:

1. If the User wants to save the current code he can click the *"Save"* button:
   1. The User is prompted with a file dialogue box in which he can navigate through his computer's file system and choose the file destination and name.
   2. The file is saved.
2. If the User wants to export his code to an object file he can click the *"Export to"* button:
   1. If his work cannot be compiled:
      1. The User is prompted with an error dialogue box that tells him that an error has occurred.
   2. The User is prompted with a file dialogue box in which he can navigate through his computer's file system and choose the file destination and name.
   3. The file is exported to an object file.
3. Use case is over.

**Alternative scenarios**: None.

**Subscenarios**: None.

**Special requirements**:
Application has access to the file system in order to save or load data.

**Additional information**: None.

## Using the application

**Description**:
The User starts the application, chooses to create new or open an existing file, and codes using the visual elements provided by the environment. The User may then run the code or save it.

**Actors**:

- The User (Programmer)

**Preconditions**: 
The application is running and **"Open file -> New file"** use case has been successfully finished.

**Postconditions**: 
Code is either run or saved to internal memory.

**Main scenario**:

1. If the User wants to load an existing file:
   1. **"Open file -> Existing file"** use case starts. After the step is finished it continues to step 2.
2. Until the User is done with the application, the following steps are repeated:
   1. If the User wants to edit the code:
      1. **"Coding"** use case starts. After this step is finished it continues to step 2.
   2. If the User wants to run the code:
      1. **"Running the code"** use case starts. After this step is finished it continues to step 2.
   3. If the User wants to save the code:
      1. **"Saving the code"** use case starts. After this step is finished it continues to step 2.
3. The User is done with the application shuts it down.

**Alternative scenarios**:

- A1: **Application exit without saving the changes**: If the User exits the application, any unsaved changes will be lost.

**Subscenarios**: None.

**Special requirements**: Application has access to the file system in order to save or load data.

**Additional information**: None.


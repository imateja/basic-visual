# Specification



## Diagrams:

- [Use cases](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/03-basicVisual/-/blob/specification/specification/use_cases/use_cases_diagram.png)
- [Components](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/03-basicVisual/-/blob/specification/specification/component_diagram.png)
- [Class](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/03-basicVisual/-/blob/specification/specification/class_diagram.png)



## Use cases:

- **Using the application:**
  - **Open file:**
    - New file
    - Existing file
  - **Coding:**
    - Import file as function
  - **Running the code:**
    - Run without steps
    - Run with steps
  - **Saving the code:**
    - Save / Save as (internal representation of code)
    - Export to object file (compile)



### Using the application

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

- **Application exit without saving the changes**: If the User exits the application, any unsaved changes will be lost.

**Subscenarios**: None.

**Special requirements**:
Application has access to the file system in order to save or load data.

**Additional information**: None.

[Using the application diagram](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/03-basicVisual/-/blob/specification/specification/use_cases/using_the_application/using_the_application.png)



### Opening the file

**Description:**
The User opened the application and can either open a new file or import an existing one and start coding.

**Actors**:

- The User (Programmer)

**Preconditions:**
The application is running.

**Postconditions:**
A new or and already existing file has been opened and is ready to be modified.

**Main scenario:**

1. User is prompted with the default scene and needs to click the *"File"* option in the navigation menu on the top of the application window.
2. The *"File"* option from the navigation menu expands, showing the user various options amongst which are the option to create and start working on a new file - option *"New"*, and the option to import an already existing file that is located on his system - option *"Open"*.

3. User chooses either option *"New"* or *"Open"* to start working on a file.
   1.  If the user chooses option *"New",* a new, empty working scene opens.
   2. If the user chooses option *"Open",* he is prompted with a file dialogue box in which he can navigate through his computers file system and chose which file he wants to open.
   3. If the file that is chosen exists, it is opened in the scene.
   4. If the file that is chosen has an invalid name or doesn't exist, the user is prompted with an error dialogue box that tells him that an error has occurred and he needs to select a different file.
4. Use case is over.

**Alternative scenarios:** None.

**Subscenarios:** None.

**Special requirements:** None.

**Additional information:** None.

[Opening the file diagram](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/03-basicVisual/-/blob/specification/specification/use_cases/open_file/open_file_sequence_diagram%20.png)



### Coding

**Description**:
The User is using GUI to create a new program by adding instruction elements to the graphics view area.

**Actors**:

- The User (Programmer)

**Preconditions**: 
The application is running.

**Postconditions**: 
Code is runnable.

**Main scenario**:

1. If the User wants to add a new instruction (*if, while, assign, for*) to the view:
   1. Click the button with the instruction name on the left toolbar.
   2. If this is not the first instruction to be added to this program:
      1. It is required to select (click) the instruction that is supposed to go before the added instruction.
2. Application is now showing the dialog box for creating the instruction:
   1. User has to fill the required fields that are marked with `""`
   2. User can fill the not required fields not marked with `""` for cosmetic changes of the graphic representation of the instruction.
   3. User can click the button *"OK"* which checks if all the required fields are filled and adds the instruction to the view and the dialog closes.
   4. While information is not valid dialog box is displayed again.
3. User can repeat steps 1 and 2.
4. Use case is over.

**Alternative scenarios**: None.

**Subscenarios**: None.

**Special requirements**: None

**Additional information**: None.

[Coding diagram](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/03-basicVisual/-/blob/specification/specification/use_cases/coding/coding_diagram_file.png)



### Running the code

**Description**: 
The User has written a code and can run it either with steps shown or not.

**Actors**: 

- The User (Programmer)

**Preconditions**: 
The application is running and visual code elements are present on the scene.

**Postconditions**: 
The code won't be changed compared to it's state before running it.

**Main scenario**: 

1. If User chooses *"Run"* option:
   1. Program will run the code and display only the final result.
2. If User chooses *"Run with steps"* option:
   1. Until there is no more instructions to execute:
      1. When the User clicks the *"Next"* button a single instruction is executed and an intermediate result is displayed.
3. Use case is over.

**Alternative scenarios**: None. 

**Subscenarios**: None. 

**Special requirements**: None. 

**Additional information**: None.

[Running the code without steps diagram](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/03-basicVisual/-/blob/specification/specification/use_cases/running_the_code/running_the_code%20(without%20steps).png)

[Running the code with steps diagram](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/03-basicVisual/-/blob/specification/specification/use_cases/running_the_code/running_the_code%20(with%20steps).png)



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

[Saving the code diagram](https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/03-basicVisual/-/blob/specification/specification/use_cases/saving_the_code/saving_the_code.png)


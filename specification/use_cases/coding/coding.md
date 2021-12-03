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

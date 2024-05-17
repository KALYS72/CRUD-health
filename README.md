# Health Track System

Health Track is a CRUD system that allows users to track their health using the World Health Organization (WHO) Health-Library system. Users can input health-related data and receive advice based on WHO guidelines.

## Features

- **Track Health Data**: Users can input various health parameters such as age, weight, height, heart rate, and chronic diseases.
- **WHO Guidelines**: The system provides advice to users based on WHO recommendations, ensuring reliable and up-to-date information.
- **CRUD Operations**: Users can perform CRUD (Create, Read, Update, Delete) operations on their health data.
- **Age Norms**: Age norms for users aged 1-18 are based on WHO growth charts.

## Presentation

For a detailed overview of the Health Track system, please refer to the [Presentation](https://github.com/KALYS72/Health-Track/blob/master/Presentation.pdf).

## Usage

1. **Clone the Repository**: 
    ```
    git clone https://github.com/KALYS72/Health-Track.git
    ```

2. **Compile and Run**: 
    ```
    cd Health-Track
    g++ -o health_track health_track.cpp
    ./health_track
    ```

3. **Follow On-Screen Instructions**: Use the program to input health data, view advice, and perform CRUD operations.

## Additional Information

- The health data is stored locally in a file named `patients.txt`.
- For more information on WHO guidelines and health recommendations, visit the [WHO website](https://www.who.int/).

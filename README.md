# C++ Command-Line Ticketing System

# Overview

This is a command-line ticketing system implemented in C++. It allows users to:

- Create new tickets with a summary and assignee
- Update ticket status (Open/In Progress/Closed)
- Search tickets by assignee
- List all tickets
- Save and load tickets to/from a CSV file for persistence

The project demonstrates **object-oriented programming (OOP), STL usage, file I/O, and CLI-based application development**.

## Features 

**1. Add Ticket**
    - Users can create a ticket with a unique ID, summary, and assignee.
    - Default values are assigned if fields are left empty.

**2. Update Status**
    - Modify the status of an existing ticket (Open/In Progress/Closed) by ID.

**3. Search by Assignee**
    - Find tickets assigned to a specific user (partial name matches allowed).

**4. List All Tickets**
    - Displays all tickets in a formatted table in the terminal.

**5. Persistent Storage**
    - Tickets are saved to tickets.csv and automatically loaded when the program starts.

## Usage

When the program runs, a menu is displayed:

=== Ticketing System ===
1. List all
2. Add ticket
3. Update status
4. Search by assignee
5. Save & Quit

Choice: 
- Enter the number of your choice and follow the prompts.
- Tickets are automatically saved to tickets.csv on exit.

## Project Motivation

This project was created as a learning exercise to strengthen C++ programming skills, practice object-oriented design, and implement file-based persistence for a terminal-based application.

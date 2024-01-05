# file details view script
# TODo add some helpfull features like file size, file type, file name, file path, 
# file modification time, file creation time, file access time,
#  file permissions, file owner, file group, file mode, file hash, file extension
# https://github.com/Akascape/CTkTable


import customtkinter as ctk
from CTkTable import CTkTable
from tkinter.filedialog import askdirectory
import os
import humanize
import time

# Create a custom tkinter window
root = ctk.CTk()

# Set the window title and size
root.title("File Summarizer")

# Set the window size
root.geometry("1000x600")

# Set the appearance mode to dark
ctk.set_appearance_mode("dark")

# Create a label to display the selected folder path
path_label = ctk.CTkLabel(root, text="No folder selected")

# Create a function to handle the folder selection
def select_folder():
    # Use the file dialog to ask for a folder name
    foldername = askdirectory()
    # Update the label with the folder path
    path_label.configure(text=foldername)
    # Get the file details and show them
    show_file_details(foldername)

# Create a function to show the file details
def show_file_details(folder_path):
    # Check if the folder path is valid
    if os.path.isdir(folder_path):
        # Create a list to store the file details
        file_details = []

        # Loop through the files in the folder
        for file in os.listdir(folder_path):
            # Get the full file path
            file_path = os.path.join(folder_path, file)

            # Get the file size in bytes
            file_size = os.path.getsize(file_path)

            # Get the file modification time
            file_time = os.path.getmtime(file_path)

            # Convert the file size to a human-readable format
            file_size_readable = humanize.naturalsize(file_size)

            # Convert the file modification time to a human-readable format
            file_time_readable = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(file_time))

            # Append the file details to the list
            file_details.append((file, file_size_readable, file_time_readable))
        
        # Create a table to show the file details with 
        table = CTkTable(master=root, values=file_details, hover_color="gray10", )
        table.pack(expand=True, padx=50, pady=15)



    else:
        # Print an error message
        print("Invalid folder path")

# Create a button to trigger the folder selection
select_button = ctk.CTkButton(root, text="Select folder", command=select_folder)

# Pack the widgets
select_button.pack(pady=10)
path_label.pack(pady=10)

# Start the main loop
root.mainloop()

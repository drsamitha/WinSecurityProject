#tkinter python gui with 3 items in dropdown list 
import tkinter as tk

def selection_changed(event):
    print("You selected", dropdown.get())

root = tk.Tk()

# Create a Tkinter variable
dropdown_var = tk.StringVar(root)

# Dictionary with options
choices = {'Option 1', 'Option 2', 'Option 3'}
dropdown_var.set('Option 1') # set the default option

dropdown = tk.OptionMenu(root, dropdown_var, *choices)
dropdown.pack()

# link function to change dropdown
dropdown_var.trace('w', selection_changed)

root.mainloop()

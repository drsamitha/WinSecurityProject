import customtkinter
from customtkinter import CTkImage, CTkLabel, CTkButton
import os
from PIL import Image  # Import the Image module

customtkinter.set_appearance_mode("System")  # Modes: system (default), light, dark
customtkinter.set_default_color_theme("blue")  # Themes: blue (default), dark-blue, green

app = customtkinter.CTk()  # create CTk window like you do with the Tk window
app.title("SecureGuardPro")  # Set the title of the window
app.geometry("960x540")

# Add image
image_path = os.path.join(os.path.dirname(__file__), 'img/start.png')
image = CTkImage(light_image=Image.open(image_path), size=(250, 250))
image_label = CTkLabel(app, image=image, text='')
image_label.place(x=350, y=150)

# Add "SecureGuard Pro" label
app_name_label = CTkLabel(app, text="SecureGuard Pro", font=("Arial", 20, "bold"))
app_name_label.place(x=20, y=20)

# Add description label with line breaks and left alignment
description_text = """Our cutting-edge unauthorized access identification tool is designed to enhance security\nmeasures by promptly detecting and alerting against any unauthorized attempts to access your systems.\nWith advanced algorithms and real-time monitoring, our application provides a robust defense against potential security\nbreaches."""
description_label = CTkLabel(app, text=description_text, font=("Arial", 12), anchor="w", justify="left")
description_label.place(x=20, y=80)

def start_function():
    print("Start button pressed")

# Use CTkButton instead of tkinter Button
start_button = CTkButton(master=app, text="Start", command=start_function)
start_button.place(relx=0.5, rely=0.9, anchor=customtkinter.CENTER)

app.mainloop()

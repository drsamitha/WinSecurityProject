import customtkinter
import os
from PIL import Image
import subprocess
import configparser


class App(customtkinter.CTk):
    def __init__(self):
        super().__init__()

        

        self.title("image_example.py")
        self.geometry("900x600")

        # set grid layout 1x2
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(1, weight=1)

        # load images with light and dark mode image
        image_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "test_images")
        self.logo_image = customtkinter.CTkImage(Image.open(os.path.join(image_path, "CustomTkinter_logo_single.png")), size=(26, 26))
        self.large_test_image = customtkinter.CTkImage(Image.open(os.path.join(image_path, "large_test_image.png")), size=(500, 150))
        self.image_icon_image = customtkinter.CTkImage(Image.open(os.path.join(image_path, "image_icon_light.png")), size=(20, 20))
        self.home_image = customtkinter.CTkImage(light_image=Image.open(os.path.join(image_path, "home_dark.png")),
                                                 dark_image=Image.open(os.path.join(image_path, "home_light.png")), size=(20, 20))
        self.chat_image = customtkinter.CTkImage(light_image=Image.open(os.path.join(image_path, "chat_dark.png")),
                                                 dark_image=Image.open(os.path.join(image_path, "chat_light.png")), size=(20, 20))
        self.add_user_image = customtkinter.CTkImage(light_image=Image.open(os.path.join(image_path, "add_user_dark.png")),
                                                     dark_image=Image.open(os.path.join(image_path, "add_user_light.png")), size=(20, 20))

        # create navigation frame
        self.navigation_frame = customtkinter.CTkFrame(self, corner_radius=0)
        self.navigation_frame.grid(row=0, column=0, sticky="nsew")
        self.navigation_frame.grid_rowconfigure(4, weight=1)

        self.navigation_frame_label = customtkinter.CTkLabel(self.navigation_frame, text="  TOOLKIT", image=self.logo_image,
                                                             compound="left", font=customtkinter.CTkFont(size=15, weight="bold"))
        self.navigation_frame_label.grid(row=0, column=0, padx=20, pady=20)

        self.home_button = customtkinter.CTkButton(self.navigation_frame, corner_radius=0, height=40, border_spacing=10, text="Home",
                                                   fg_color="transparent", text_color=("gray10", "gray90"), hover_color=("gray70", "gray30"),
                                                   image=self.home_image, anchor="w", command=self.home_button_event)
        self.home_button.grid(row=1, column=0, sticky="ew")

        self.frame_2_button = customtkinter.CTkButton(self.navigation_frame, corner_radius=0, height=40, border_spacing=10, text="HELPS",
                                                      fg_color="transparent", text_color=("gray10", "gray90"), hover_color=("gray70", "gray30"),
                                                      image=self.chat_image, anchor="w", command=self.frame_2_button_event)
        self.frame_2_button.grid(row=2, column=0, sticky="ew")

        self.frame_3_button = customtkinter.CTkButton(self.navigation_frame, corner_radius=0, height=40, border_spacing=10, text="ABOUT",
                                                      fg_color="transparent", text_color=("gray10", "gray90"), hover_color=("gray70", "gray30"),
                                                      image=self.add_user_image, anchor="w", command=self.frame_3_button_event)
        self.frame_3_button.grid(row=3, column=0, sticky="ew")

        self.appearance_mode_menu = customtkinter.CTkOptionMenu(self.navigation_frame, values=["Light", "Dark", "System"],
                                                                command=self.change_appearance_mode_event)
        self.appearance_mode_menu.grid(row=6, column=0, padx=20, pady=20, sticky="s")

        # self.scaling_label = customtkinter.CTkLabel(self.navigation_frame, text="UI Scaling:", anchor="w")
        # self.scaling_label.grid(row=7, column=0, padx=20, pady=(10, 0))
        self.scaling_optionemenu = customtkinter.CTkOptionMenu(self.navigation_frame, values=["80%", "90%", "100%", "110%", "120%"],
                                                               command=self.change_scaling_event)
        self.scaling_optionemenu.grid(row=8, column=0, padx=20, pady=(10, 20))


        # create home frame
        self.home_frame = customtkinter.CTkFrame(self, corner_radius=0, fg_color="transparent")
        self.home_frame.grid_columnconfigure(0, weight=1)

        self.home_frame_large_image_label = customtkinter.CTkLabel(self.home_frame, text="", image=self.large_test_image)
        self.home_frame_large_image_label.grid(row=0, column=0, padx=20, pady=10)


        # Add 3 switches directly to the home frame
        self.switch_frame = customtkinter.CTkFrame(self.home_frame)
        self.switch_frame.grid(row=2, column=0, padx=(20, 20), pady=(20, 0), sticky="nswe")
        self.switch_1 = customtkinter.CTkSwitch(master=self.switch_frame, text="Mannual Permission service")
        self.switch_1.grid(row=1, column=0, padx=10, pady=10)

        self.switch_2 = customtkinter.CTkSwitch(master=self.switch_frame, text="Background Services disable")
        self.switch_2.grid(row=2, column=0, padx=10, pady=10, sticky="w")

        self.switch_3 = customtkinter.CTkSwitch(master=self.switch_frame, text="Defender Submission block")
        self.switch_3.grid(row=3, column=0, padx=10, pady=10)

        
        # create checkbox and switch frame
        self.checkbox_slider_frame = customtkinter.CTkFrame(self.home_frame)
        self.checkbox_slider_frame.grid(row=6, column=0, padx=(20, 20), pady=(20, 0), sticky="nsew")
        self.checkbox_1 = customtkinter.CTkCheckBox(master=self.checkbox_slider_frame, text="Basic IP block")
        self.checkbox_1.grid(row=1, column=0, pady=(20, 0), padx=20, sticky="n")
        
        self.checkbox_3 = customtkinter.CTkCheckBox(master=self.checkbox_slider_frame, text="Force IP block")
        self.checkbox_3.grid(row=2, column=0, pady=20, padx=20, sticky="n")


        # create window openning 
        self.summery_button = customtkinter.CTkButton(self.home_frame, text="File summery", command=self.openFS)
        self.summery_button.grid(row=8, column=0, padx=20, pady=10, sticky="wnse")        

        # create last entry and button
        self.main_button_1 = customtkinter.CTkEntry(self.home_frame, placeholder_text="Advanced_tools")
        self.main_button_1 = customtkinter.CTkButton(master=self.home_frame, fg_color="transparent", border_width=2, text="Advanced", text_color=("gray10", "#DCE4EE"))
        self.main_button_1.grid(row=9, column=0, padx=20, pady=10, sticky="w")

        

        self.home_frame_button_1 = customtkinter.CTkButton(self.home_frame, text="START", command=self.START)
        self.home_frame_button_1.grid(row=9, column=0, padx=20, pady=10, sticky="se")  # Add sticky="se" for bottom-right corner

        # create second frame
        self.second_frame = customtkinter.CTkFrame(self, corner_radius=0, fg_color="transparent")
        self.second_frame.grid_columnconfigure(0, weight=1)

        # create window openning log of the program
        self.logger = customtkinter.CTkButton(self.second_frame, text="Open Log", command=self.open_input_dialog_event)
        self.logger = customtkinter.CTkButton(master=self.second_frame, fg_color="transparent", border_width=2, text="Open Log", text_color=("gray10", "#DCE4EE"))
        self.logger.grid(row=8, column=0, padx=20, pady=10, sticky="wse") 



        # create third frame
        self.third_frame = customtkinter.CTkFrame(self, corner_radius=0, fg_color="transparent")

        # need to make button for update the tool
        self.update_button = customtkinter.CTkButton(self.third_frame, text="UPDATE", command=self.update_button_event)
        self.update_button.grid(row=0, column=0, padx=20, pady=10)
        self.update_button.configure(fg_color=("black", "white"))
        self.update_button.configure(text_color=("white", "black"))
        self.update_button.configure(hover_color=("gray70", "gray30"))
        
                # Initialize ConfigParser
        self.config = configparser.ConfigParser()

        # Load settings at application start
        self.load_settings()



        # select default frame
        self.select_frame_by_name("home")

    def select_frame_by_name(self, name):
        # set button color for selected button
        self.home_button.configure(fg_color=("gray75", "gray25") if name == "home" else "transparent")
        self.frame_2_button.configure(fg_color=("gray75", "gray25") if name == "frame_2" else "transparent")
        self.frame_3_button.configure(fg_color=("gray75", "gray25") if name == "frame_3" else "transparent")

        # show selected frame
        if name == "home":
            self.home_frame.grid(row=0, column=1, sticky="nsew")
        else:
            self.home_frame.grid_forget()
        if name == "frame_2":
            self.second_frame.grid(row=0, column=1, sticky="nsew")
        else:
            self.second_frame.grid_forget()
        if name == "frame_3":
            self.third_frame.grid(row=0, column=1, sticky="nsew")
        else:
            self.third_frame.grid_forget()

    def home_button_event(self):
        self.select_frame_by_name("home")

    def frame_2_button_event(self):
        self.select_frame_by_name("frame_2")

    def frame_3_button_event(self):
        self.select_frame_by_name("frame_3")

    def openFS(self):
        subprocess.run(["python", "fileSummr.py"])

    def open_input_dialog_event(self):
        dialog = customtkinter.CTkInputDialog(text="Type in a number:", title="CTkInputDialog")
        print("CTkInputDialog:", dialog.get_input())

    def change_appearance_mode_event(self, new_appearance_mode):
        customtkinter.set_appearance_mode(new_appearance_mode)

    def change_scaling_event(self, new_scaling: str):
        new_scaling_float = int(new_scaling.replace("%", "")) / 100
        customtkinter.set_widget_scaling(new_scaling_float)

    def START(self):
        if self.checkbox_1.get() == 1:  # Check if the checkbox is selected
            # Run the "bock" binary
            subprocess.run(["./basicblock"])  # Modify the path accordingly
            # print state of the checkbox_1 to console
            # print(self.checkbox_1.get())


        else:
            # Run the "unblock" binary
            subprocess.run(["./basicunblock"])  # Modify the path accordingly
            # print(self.checkbox_1.get())

        if self.checkbox_3.get() == 1:
            # Run the "forceblock" binary
            subprocess.run(["./forceblock"])  # Modify the path accordingly
        else:
            # Run the "forceunblock" binary
            subprocess.run(["./forceunblock"])


        # run serviceToggle binary according to the state of the switch 2
        if self.switch_2.get() == 1:
            subprocess.run(["./serviceToggle", "--stop"])
            print("Background Services disabled")    

        else:
            subprocess.run(["./serviceToggle", "--start"])
            print("Background Services enabled")

        # run defenderToggle binary according to the state of the switch 3
        if self.switch_3.get() == 1:
            subprocess.run(["./defenderSubmissionToggle", "--stop"])
            print("Defender Submission block")

        else:
            subprocess.run(["./defenderSubmissionToggle", "--start"])
            print("Defender Submission unblock")

        

    def update_button_event(self):
        print("update click")

    def save_settings(self):
        settings = {
            "checkbox_1": self.checkbox_1.get(),
            "checkbox_3": self.checkbox_3.get(),
            "switch_1": self.switch_1.get(),
            "switch_2": self.switch_2.get(),
            "switch_3": self.switch_3.get(),
            "appearance": self.appearance_mode_menu.get(),
            "scale": int(self.scaling_optionemenu.get().rstrip("%")),  # Convert to int
        }

        self.config["Settings"] = settings

        with open("settings.ini", "w") as configfile:
            self.config.write(configfile)


    def load_settings(self):
        self.config.read("settings.ini")

        try:
            settings = self.config["Settings"]

            # Set the state of checkboxes using the custom method if available
            if hasattr(self.checkbox_1, 'set'):
                self.checkbox_1.set(int(settings.get("checkbox_1", 0)))
            else:
                self.checkbox_1.select() if int(settings.get("checkbox_1", 0)) == 1 else self.checkbox_1.deselect()

            if hasattr(self.checkbox_3, 'set'):
                self.checkbox_3.set(int(settings.get("checkbox_3", 0)))
            else:
                self.checkbox_3.select() if int(settings.get("checkbox_3", 0)) == 1 else self.checkbox_3.deselect()

            # Set the state of switches from settins.ini 
            if "switch_1" in settings:
                self.switch_1.toggle() if int(settings["switch_1"]) == 1 else None
            if "switch_2" in settings:
                self.switch_2.toggle() if int(settings["switch_2"]) == 1 else None
            if "switch_3" in settings:
                self.switch_3.toggle() if int(settings["switch_3"]) == 1 else None
            
            # ... (set the state of other components)

        except KeyError:
            # Handle missing keys gracefully, e.g., set default values
            pass


    def on_closing(self):
        # This function will be called when the user closes the window
        self.save_settings()
        self.destroy()



        
    

if __name__ == "__main__":
    app = App()
    # Bind the on_closing method to the close button event
    app.protocol("WM_DELETE_WINDOW", app.on_closing)
    app.mainloop()


import tkinter as tk
from tkinter import ttk

class View(tk.Tk):
    def __init__(self, model, controller):
        super(View, self).__init__()
        self.model = model
        self.controller = controller

        self.init_window()
        self.fra_container = ttk.Frame(self)

        self.init_human(self.fra_container)
        self.init_distance(self.fra_container)

        self.init_all_sensors(self.fra_container)

        self.fra_container.pack()

    def init_window(self):
        """
        Builds the window
        """
        # Settings
        WindowWidth = 1000
        WindowHeight = 500
        self.title('Sensor simulation')

        # Size
        screenWidth = self.winfo_screenwidth()
        screenHeight = self.winfo_screenheight()
        xOffset = screenWidth / 2 - WindowWidth / 2
        yOffset = screenHeight / 2 - WindowHeight / 2
        self.geometry(str(WindowWidth) + 'x' + str(WindowHeight) + '+' + str(round(xOffset)) + '+' + str(round(yOffset)))
        self.minsize(500, 500)
        pass

    def init_human(self, container):
        """
        Creates the human figure on the container
        """
        self.frm_human = tk.Canvas(container,
                              width = 500,
                              height = 160)
        self.img_human = tk.PhotoImage(file = "./human.png")
        self.img_human = self.img_human.subsample(5, 5)
        self.frm_human.grid(row = "2",
                       column = "1",
                       rowspan = "3")
        self.human = self.frm_human.create_image(0, 0, image = self.img_human)
        self.frm_human.moveto(self.human, 475 - 500/30*self.model.distance, 0)
        pass

    def init_distance(self, container):
        """
        Creates the distance (incl. slider) and tolerance widgets on the container
        """
        self.fra_distance = ttk.Frame(container)
        self.str_distance = tk.StringVar()
        self.str_distance.set(str(self.model.distance))
        self.txt_distance = tk.Entry(self.fra_distance,
                                    width = "10",
                                    textvariable = self.str_distance)
        self.txt_distance.pack(side = "left")

        self.lbl_distance_unit = ttk.Label(self.fra_distance,
                                      text = " m +/- ")
        self.lbl_distance_unit.pack(side = "left")

        self.str_tolerance = tk.StringVar()
        self.str_tolerance.set(str(self.model.tolerance))
        self.str_tolerance.trace("w", self.controller.update_str_tolerance)
        self.txt_tolerance = tk.Entry(self.fra_distance,
                                     width = "10",
                                     textvariable = self.str_tolerance)
        self.txt_tolerance.pack(side = "left")
        self.lbl_tolerance_unit = ttk.Label(self.fra_distance,
                                            text = " m")
        self.lbl_tolerance_unit.pack()

        self.fra_distance.grid(row = "4",
                               column = "2")

        frm_arrow = tk.Canvas(container,
                              height = 30)
        frm_arrow.grid(row = "5",
                       column = "1",
                       columnspan = "2",
                       sticky = "ew")
        frm_arrow.create_line(0, 15, 670, 15, arrow=tk.BOTH)
        self.hsb_distance = ttk.Scale(container,
                                        from_ = 30,
                                        to = 0,
                                        variable = self.model.distance,
                                        command = self.controller.update_hsb_distance)
        self.hsb_distance.grid(row = "6",
                               column = "1",
                               sticky = "ew")
        pass

    def init_all_sensors(self, container):
        """
        Creates all widgets related to the sensors on the container
        """
        self.lbl_sensor_auto = ttk.Label(container,
                                         text = "Auto")
        self.lbl_sensor_auto.grid(row = "1",
                                  column = "4")

        self.lbl_sensor_error = ttk.Label(container,
                                         text = "Error")
        self.lbl_sensor_error.grid(row = "1",
                                  column = "5")

        self.chk_sensor_auto = {}
        self.bool_sensor_auto = {}
        self.bool_sensor_error = {}
        self.chk_sensor_error = {}
        self.str_sensor_distance = {}
        self.txt_sensor_distance = {}
        self.lbl_sensor = {}
        self.lbl_sensor_current = {}
        self.fra_sensor_values = {}

        self.init_sensor(container, 1)
        self.init_sensor(container, 2)
        self.init_sensor(container, 3)
        pass

    def init_sensor(self, container, sensor_number):
        """
        Creates all widgets for a specific sensor "sensor_number" on the container
        """
        self.bool_sensor_auto[sensor_number-1] = tk.BooleanVar()
        self.bool_sensor_auto[sensor_number-1].set(self.model.sensor_auto[sensor_number-1])
        self.chk_sensor_auto[sensor_number-1] = ttk.Checkbutton(container,
                                                                variable = self.bool_sensor_auto[sensor_number-1],
                                                                onvalue = True,
                                                                offvalue = False,
                                                                command = self.controller.update_sensor_auto)
        self.chk_sensor_auto[sensor_number-1].grid(row = str(sensor_number + 1),
                                                  column = "4")

        self.bool_sensor_error[sensor_number-1] = tk.BooleanVar()
        self.bool_sensor_error[sensor_number-1].set(self.model.sensor_error[sensor_number-1])
        self.chk_sensor_error[sensor_number-1] = ttk.Checkbutton(container,
                                                                 variable = self.bool_sensor_error[sensor_number-1],
                                                                 onvalue = True,
                                                                 offvalue = False,
                                                                 command = self.controller.update_sensor_error)
        self.chk_sensor_error[sensor_number-1].grid(row = str(sensor_number + 1),
                                                   column = "5")

        self.fra_sensor_values[sensor_number-1] = ttk.Frame(container)
        self.str_sensor_distance[sensor_number-1] = tk.StringVar()
        self.txt_sensor_distance[sensor_number-1] = tk.Entry(self.fra_sensor_values[sensor_number-1],
                                                            width = 5,
                                                            textvariable = self.str_sensor_distance[sensor_number-1])
        self.txt_sensor_distance[sensor_number-1].pack(side = "left")

        self.lbl_sensor[sensor_number-1] = ttk.Label(self.fra_sensor_values[sensor_number-1],
                                                     text = " m --> ")
        self.lbl_sensor[sensor_number-1].pack(side = "left")

        self.lbl_sensor_current[sensor_number-1] = ttk.Label(self.fra_sensor_values[sensor_number-1],
                                                             width = 3)
        self.lbl_sensor_current[sensor_number-1].pack(side = "left")
        sensor_current_unit = ttk.Label(self.fra_sensor_values[sensor_number-1],
                                        text = "/10 mA")
        sensor_current_unit.pack(side = "left")
        self.fra_sensor_values[sensor_number-1].grid(row = str(sensor_number + 1),
                                    column = "6")
        pass

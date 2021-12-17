class Controller:
    """docstring for Controller."""

    def __init__(self, model):
        super(Controller, self).__init__()
        self.model = model
        pass

    def set_view(self, view):
        self.view = view
        pass

    def update_hsb_distance(self, event):
        '''
        Gets called when the distance slider gets updated
        '''
        self.model.distance = float(self.view.hsb_distance.get())
        self.view.str_distance.set(str(self.model.distance))
        self.view.frm_human.moveto(self.view.human, 475 - 500/30*self.model.distance, 0)

    def update_str_distance(self, *args):
        """
        Gets called when the distance in the text-box gets updated
        """
        self.model.distance = float(self.view.str_distance.get())
        self.view.hsb_distance.set(self.model.distance)

    def update_str_tolerance(self, *args):
        """
        Gets called when the string in the tolerance-text-box gets updated
        """
        self.model.tolerance = float(self.view.str_tolerance.get())

    def update_sensor_auto(self):
        """
        Gets called when one of the checkboxes in the column "auto" changes its value
        """
        sensor_auto = {}
        sensor_auto[0] = self.view.bool_sensor_auto[0].get()
        sensor_auto[1] = self.view.bool_sensor_auto[1].get()
        sensor_auto[2] = self.view.bool_sensor_auto[2].get()
        self.model.sensor_auto = sensor_auto

    def update_sensor_error(self):
        """
        Gets called when one of the checkboxes in the column "error" changes its value
        """
        sensor_error = {}
        sensor_error[0] = self.view.bool_sensor_error[0].get()
        sensor_error[1] = self.view.bool_sensor_error[1].get()
        sensor_error[2] = self.view.bool_sensor_error[2].get()
        self.model.sensor_error = sensor_error

    def update_sensor_distance(self, event):
        """
        Gets called when one of the sensor distances gets changed by user input
        """
        sensor_distance = {}
        sensor_distance[0] = float(self.view.str_sensor_distance[0].get())
        sensor_distance[1] = float(self.view.str_sensor_distance[1].get())
        sensor_distance[2] = float(self.view.str_sensor_distance[2].get())
        self.model.sensor_distance = sensor_distance

    def update(self):
        """
        Recalculate the sensor current values and write them to file. Repeat after 10 ms
        """
        self.model.calculate_all_sensor_values()
        if (self.model.sensor_auto[0]):
            self.view.str_sensor_distance[0].set(str(self.model.sensor_distance[0]))
        if (self.model.sensor_auto[1]):
            self.view.str_sensor_distance[1].set(str(self.model.sensor_distance[1]))
        if (self.model.sensor_auto[2]):
            self.view.str_sensor_distance[2].set(str(self.model.sensor_distance[2]))
        self.view.lbl_sensor_current[0]["text"] = str(self.model.sensor_current[0])
        self.view.lbl_sensor_current[1]["text"] = str(self.model.sensor_current[1])
        self.view.lbl_sensor_current[2]["text"] = str(self.model.sensor_current[2])

        self.model.write_sensor_currents()
        self.view.after(10, self.update)
        pass

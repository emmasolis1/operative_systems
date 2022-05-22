# Author: Emmanuel D. Solis

class Header:
  def __init__(self, max_size_node, max_size_disk, address) -> None:
    self.max_storage = max_size_node
    self.total_spaces = int(max_size_disk)
    self.free_spaces = int(max_size_disk)
    self.file_name = "NoName"
    self.address = str(address)
    self.is_occupied = False
    #self.print_header_info()
  
  def print_header_info(self):
    toString = "File Name: " + str(self.file_name)
    toString += "\nAddress: " + str(self.address)
    toString += "\nTotal Spaces: " + str(self.total_spaces)
    toString += "\nFree Spaces: " + str(self.free_spaces)
    toString += "\n"
    print(toString)

  def set_file_name(self, name):
    self.file_name = name
  
  def set_occupied_status(self, status):
    self.is_occupied = status

  def add_element_saved(self):
    self.free_spaces -= 1

  def get_total_spaces(self):
    return self.total_spaces
  
  def get_free_spaces(self):
    return self.free_spaces

  def get_file_name(self):
    return self.file_name

  def get_file_address(self):
    return self.address

  def get_occupied_status(self):
    return self.is_occupied

class Disk:
  def __init__(self) -> None:
    # Disk matrix dimensions.
      self.disk_rows = 10 # Must be even number.
      self.disk_colums = 10
      self.disk_size = self.disk_rows * self.disk_colums
      # Size of the blocks.
      self.max_elements_peer_space = 2
      # Intializes the disk spaces.
      self.buffer = [0] * self.disk_colums
      while self.disk_rows % 2 != 0:
        print("Disk rows must be an even number, please re-enter it:")
        self.disk_rows = int(input())
      # Fill reference nodes with -1. Data nodes with -2.
      for x in range (0, int(self.disk_rows/2)):
        self.buffer[x] = [0] * self.disk_colums
        for y in range (self.disk_colums):
          if x == 0 and y != 0:
            address = str(int(self.disk_rows/2)) + "," + str(y)
          else:
            address = str(x + int(self.disk_rows/2)) + "," + str(y)
          self.buffer[x][y] = Header(self.max_elements_peer_space, self.max_elements_peer_space, address)
      for x in range (int(self.disk_rows/2), int(self.disk_rows)):
        self.buffer[x] = [0] * self.disk_colums
        for y in range (self.disk_colums):
          self.buffer[x][y] = "Data"
      self.buffer[0][0] = None

  def print_nodes_info(self):
    for x in range (int(self.disk_rows/2)):
      for y in range(self.disk_colums):
        if x == 0 and y == 0:
          pass
        else:
          print(self.buffer[x][y].print_header_info())

  def print_disk_data(self):
    print("FLASH DRIVE:")
    for x in range(int(self.disk_rows/2), int(self.disk_rows)):
      print(self.buffer[x]) 

  # Function that print a file data usign it's name. Completes the point 1 of the project.
  def open_file(self, file_name):
    found = False
    data = None
    for x in range (int(self.disk_rows/2)):
      if found == True:
        break
      for y in range(int(self.disk_colums)):
        if found == True:
          break
        if x == 0 and y == 0:
          None
        else:
          if self.buffer[x][y].get_file_name() is file_name:
          #if self.buffer[x][y].get_occupied_status() == True:
            address = self.buffer[x][y].get_file_address().split(',')
            x_pos = int(address[0])
            y_pos = int(address[1])
            data = self.buffer[x_pos][y_pos]
      # Checks if found the file.
      if data == None:
        data = "File does not exist."
    return data

  # Function that adds a new file to the disk. Completes the point 2 of the project.  
  def add_new_file(self, file_name, data):
    # Searches if file name is already in disk.
    while self.open_file(file_name) != "File does not exist.":
      print("File already exist, please enter another name.")
      file_name = input()
    # Adds the file in ths address that has the first found free i-node.
    disk_full = True # Assume that is full, prove contrary.
    element_saved = False
    address = str()
    for x in range(int(self.disk_rows/2)):
      if disk_full == False or element_saved == True:
        break
      for y in range(int(self.disk_colums)):
        if element_saved == True:
          break
        if x == 0 and y == 0:
          None
        else:
          if self.buffer[x][y].get_occupied_status() == False:
            disk_full = False
            address = self.buffer[x][y].get_file_address()
            self.buffer[x][y].set_file_name(file_name)
            self.buffer[x][y].set_occupied_status(True)
            self.buffer[x][y].add_element_saved()
            element_saved = True
            break
    if disk_full == True:
      print("Unable to storage file. Disk is full.")
    else:
      address = address.split(',')
      x_pos = int(address[0])
      y_pos = int(address[1])
      self.buffer[x_pos][y_pos] = str(data)
      print("Data:", data, "saved succesfully in address", address, "with name", file_name)

  # Funcion that adds data to an already existent file in the disk. Completes the point 3 of the project.
  def add_data_to_file(self, file, data):
    found = False
    for x in range(int(self.disk_rows/2)):
      if found == True:
        break
      for y in range(int(self.disk_colums)):
        if found == True:
          break
        if x == 0 and y == 0:
          None
        else:
          if self.buffer[x][y].get_file_name() is file:
            found = True
            if self.buffer[x][y].get_free_spaces() > 0: # Means there is still space free in this block.
              address = self.buffer[x][y].get_file_address()
              address = address.split(',')
              x_pos = int(address[0])
              y_pos = int(address[1])
              self.buffer[x_pos][y_pos] += str(data)
              print("Data", data, "added succesfully to file", file, "in address", address)
            else:
              print("Unable to add data. Block for this file is already at its max capacity.")
    if found == False:
      print("Unable to add data. File with the name", file, "does not exist.")

  def show_menu(self):
    menu = "Enter an option:"
    menu += "\n0. Exit."
    menu += "\n1. Open an existent file."
    menu += "\n2. Save a new file."
    menu += "\n3. Add data to an existent file."
    menu += "\n4. Print I-Nodes status."
    menu += "\n5. Print Disk status."
    while True:
      print(menu)
      try:
        option = int(input())
      except ValueError:
        print("You had to enter a number, closing system...")
        break
      if option == 0:
        print("Closing file system.")
        break
      elif option == 1:
        file_name = input("Enter the file name to search.\n")
        print(self.open_file(file_name))
      elif option == 2:
        file_name = input("Enter the new file name.\n")
        data = input("Enter the data to save in this file.\n")
        self.add_new_file(file_name, data)
      elif option == 3:
        file_name = input("Enter the file name in which you want to add new data.\n")
        data = input("Enter the data to add to this file.\n")
        self.add_data_to_file(file_name, data)
      elif option == 4:
        self.print_nodes_info()
      elif option == 5:
        self.print_disk_data()
      else:
        break

if __name__ == '__main__':
  my_disk = Disk()
  my_disk.show_menu()
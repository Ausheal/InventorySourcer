import _inventory_sourcer
import numpy as np
import customtkinter
import os
import pandas as pd
from dotenv import load_dotenv

load_dotenv() 
API_KEY=os.getenv('api_key')

file_path = 'data.csv'
file_exists = os.path.exists(file_path)
data_list = []

checked_inStock = customtkinter.StringVar(value="off")
title = customtkinter.StringVar()
ID = customtkinter.StringVar()
url = customtkinter.StringVar()
price = customtkinter.DoubleVar()
quantity = customtkinter.IntVar()



def cpp_ebay_finder (product_search) : 
    """ EBAY Finder 
	Parameters
	----------

	Returns
	-------

	"""

    data_list.append(_inventory_sourcer.ebay_finder(product_search))

    return data_list

def cpp_Manual_add_inventory (new_title, new_ID, new_url, new_price, new_quantity, new_stock): 
    """ Manual Inventory Adder
	Parameters
	----------

	Returns
	-------

	"""

    data_list.append(_inventory_sourcer.manual_add(new_title, new_ID, new_url, new_price, new_quantity, new_stock))

    return data_list

def ReadCSV(): 
	
	df = pd.read_csv(file_path)
	df.dropna(inplace = True)

	
def WriteCSV():
	df = pd.DataFrame(data_list)
	data_list.to_csv(file_path, mode='a', index=False, header=not file_exists)


def button_callback():
	got_title = title.get()
	got_ID = ID.get()
	got_url = url.get()
	got_price = price.get()
	got_quantity = quantity.get()
	inStock = checked_inStock.get()
	cpp_Manual_add_inventory(got_title, got_ID, got_url, got_price, got_quantity, inStock)


def main (): 
	app = customtkinter.CTk()
	app.geometry("400x150")

	entry = customtkinter.CTkEntry(app,textvariable=title, placeholder_text="Title")
	entry.grid(row=1, column=0, padx=20, pady=(0, 20), sticky="w")

	entry2 = customtkinter.CTkEntry(app,textvariable=ID, placeholder_text="ID")
	entry2.grid(row=1, column=1, padx=20, pady=(0, 20), sticky="w")

	entry3 = customtkinter.CTkEntry(app,textvariable=url, placeholder_text="URL")
	entry3.grid(row=2, column=0, padx=20, pady=(0, 20), sticky="w")

	entry4 = customtkinter.CTkEntry(app,textvariable=price, placeholder_text="Price")
	entry4.grid(row=3, column=0, padx=20, pady=(0, 20), sticky="w")

	entry5 = customtkinter.CTkEntry(app,textvariable=quantity, placeholder_text="Quantity")
	entry5.grid(row=3, column=1, padx=20, pady=(0, 20), sticky="w")

	checkbox_1 = customtkinter.CTkCheckBox(app, text="in stock", variable=checked_inStock)
	checkbox_1.grid(row=4, column=0, padx=20, pady=(0, 20), sticky="w")
	


	checked_inStock = customtkinter.BooleanVar()

	button = customtkinter.CTkButton(app, text="my button", command=button_callback)
	button.grid(row=5, column=0, padx=20, pady=20, sticky="ew", columnspan=2)

	app.mainloop()



if __name__ == "__main__":
    main()

input("Press Enter to exit")
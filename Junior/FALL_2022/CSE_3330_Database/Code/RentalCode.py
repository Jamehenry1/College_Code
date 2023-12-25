
# -- PyQt5 pip install PyQt5

# -- Tkinter pip install tkinter 

# -- Kivy   pip install kivy

from tkinter import *
from tkinter.font import Font, nametofont

import sqlite3

from datetime import date

# create tkinter window 

root = Tk()

root.title('Rentals')

root.geometry("750x820")
root.configure(background='#0064B1')

address_book_connect = sqlite3.connect('CarRental2019.sql')

address_book_cur = address_book_connect.cursor()
listbox = Listbox(root, width=100, height=10)

def submitCustomer():
	submit_conn = sqlite3.connect('CR.db')

	submit_cur = submit_conn.cursor()

	submit_cur.execute("INSERT INTO CUSTOMER(Name, Phone) VALUES (:name, :phone) ",
		{
			'name': name.get(),
			'phone': phone.get()
		})
    
	#commit changes
    
	submit_conn.commit()
	#close the DB connection
	submit_conn.close()



def submitVehicle():
	submit_conn = sqlite3.connect('CR.db')

	submit_cur = submit_conn.cursor()

	submit_cur.execute("INSERT INTO VEHICLE VALUES (:VehicleID, :Description, :Year, :Category, :Type ) ",
		{
			'VehicleID': vehicleid.get(),
			'Description': description.get(),
            'Year': year.get(),
            'Category': category.get(),
            'Type': cartype.get()
		})

	#commit changes

	submit_conn.commit()
	#close the DB connection
	submit_conn.close()



def submitRental():
    submit_conn = sqlite3.connect('CR.db')

    submit_cur = submit_conn.cursor()
    
    vehicleid2 = submit_cur.execute("SELECT VehicleID FROM VEHICLE WHERE Type = :Type AND Category = :Category AND VehicleID NOT IN (SELECT VehicleID FROM RENTAL WHERE StartDate BETWEEN :StartDate AND :ReturnDate OR ReturnDate BETWEEN :StartDate AND :ReturnDate)",
        {
            'Type': cartype2.get(),
            'Category': category2.get(),
            'StartDate': startdate.get(),
            'ReturnDate': returndate.get()
        }).fetchall()[0][0]
    
    rate = 0
    
    if rentaltype.get() == '7':
        rate = submit_cur.execute('''SELECT Weekly FROM RATE WHERE Type = :Type AND Category = :Category''',
            {
                'Type': cartype2.get(),
                'Category': category2.get()
            }).fetchall()[0][0]
    else:
        rate = submit_cur.execute('''SELECT Daily FROM RATE WHERE Type = :Type AND Category = :Category''',
            {
                'Type': cartype2.get(),
                'Category': category2.get()
            }).fetchall()[0][0]
    
    totalamount = int(rate) * int(qty.get())
    
    returned = 1
    paydate = paymentdate.get()
    if len(paymentdate.get()) == 0:
        returned = 0
        paydate = 'NULL'

    submit_cur.execute("INSERT INTO RENTAL VALUES (:CustID, :VehicleID, :StartDate, :OrderDate, :RentalType, :Qty, :ReturnDate, :TotalAmount, :PaymentDate, :Returned ) ",
        {
            'CustID': custid.get(), 
            'VehicleID': vehicleid2, 
            'StartDate': startdate.get(), 
            'OrderDate': date.today().strftime("%Y-%m-%d"), 
            'RentalType': rentaltype.get(), 
            'Qty': qty.get(), 
            'ReturnDate': returndate.get(), 
            'TotalAmount': totalamount, 
            'PaymentDate': paydate, 
            'Returned': returned
        })

	#commit changes

    submit_conn.commit()
	#close the DB connection
    submit_conn.close()


def return_rental_query():

    iq_conn = sqlite3.connect('CR.db')

    iq_cur = iq_conn.cursor()

    returncustid = iq_cur.execute("SELECT CustID FROM CUSTOMER WHERE Name = ?", 
                        (name2.get(),)).fetchall()[0][0]
    
    totalamount = iq_cur.execute("SELECT TotalAmount FROM RENTAL WHERE CustID = ? AND VehicleID = ? AND ReturnDate = ?", 
                        (returncustid, vehicleid3.get(), returndate2.get(),)).fetchall()[0][0]

    print_record = 'Your payment due is ' + str(totalamount)

    iq_label = Label(root, text = print_record)

    iq_label.grid(row = 22, column = 0, columnspan = 2)
    
    iq_cur.execute("UPDATE RENTAL SET Returned = 1, PaymentDate = ? WHERE CustID = ? AND VehicleID = ? AND ReturnDate = ?", 
                        (date.today().strftime("%Y-%m-%d"), returncustid, vehicleid3.get(), returndate2.get(),))
    
	#commit changes

    iq_conn.commit()
	#close the DB connection
    iq_conn.close()



def customer_balance_query():
    iq_conn = sqlite3.connect('CR.db')

    iq_cur = iq_conn.cursor()
    
    custidbalance = custid2.get()
    if len(custidbalance) > 0:
        iq_cur.execute('''SELECT *
                        FROM (SELECT CustID, Name, '$' || SUM(CASE WHEN Returned = 0 THEN TotalAmount ELSE 0 END) || '.00' Balance
                        FROM CUSTOMER C NATURAL JOIN RENTAL R
                        GROUP BY CustID
                        UNION
                        SELECT CustID, Name, '$0.00' Balance
                        FROM CUSTOMER
                        WHERE CustID NOT IN
                            (SELECT CustID
                            FROM CUSTOMER NATURAL JOIN RENTAL
                            GROUP BY CustID)
                        GROUP BY CustID)
                        WHERE CustID = :CustID
                        ''',
        {
            'CustID': custid2.get()
        })
    else:
        iq_cur.execute('''SELECT *
                        FROM (SELECT CustID, Name, '$' || SUM(CASE WHEN Returned = 0 THEN TotalAmount ELSE 0 END) || '.00' Balance
                        FROM CUSTOMER C NATURAL JOIN RENTAL R
                        GROUP BY CustID
                        UNION
                        SELECT CustID, Name, '$0.00' Balance
                        FROM CUSTOMER
                        WHERE CustID NOT IN
                            (SELECT CustID
                            FROM CUSTOMER NATURAL JOIN RENTAL
                            GROUP BY CustID)
                        GROUP BY CustID)
                        WHERE Name LIKE ?
                        ''', ('%' + name3.get() + '%',))
       
    output_records = iq_cur.fetchall()

    print_record = ''

    for output_record in output_records:
        print_record += str(output_record[0]) + " " + str(output_record[1]) + " " + str(output_record[2]) + "\n"
    
    listbox.delete(0, END)
    for line in print_record.split('\n'):
        listbox.insert(END, line)
	
	#commit changes

    iq_conn.commit()
	#close the DB connection
    iq_conn.close()



def vehicle_rate_query():
    iq_conn = sqlite3.connect('CR.db')

    iq_cur = iq_conn.cursor()
    
    vehiclerateid = vehicleid4.get()
    if len(vehiclerateid) > 0:
        iq_cur.execute('''SELECT *
                        FROM (SELECT VehicleID, Description, '$' || ROUND(AVG(TotalAmount / (RentalType * Qty)), 1) || '0' DailyRate
                        FROM VEHICLE NATURAL JOIN RENTAL
                        GROUP BY VehicleID
                        UNION
                        SELECT VehicleID, Description, 'Non-Applicable'
                        FROM VEHICLE
                        WHERE VehicleID NOT IN (SELECT VehicleID FROM RENTAL))
                        WHERE VehicleID = :VehicleID
                        GROUP BY VehicleID
                        ''',
        {
            'VehicleID': vehicleid4.get()
        })
    else:
        iq_cur.execute('''SELECT *
                        FROM (SELECT VehicleID, Description, '$' || ROUND(AVG(TotalAmount / (RentalType * Qty)), 1) || '0' DailyRate
                        FROM VEHICLE NATURAL JOIN RENTAL
                        GROUP BY VehicleID
                        UNION
                        SELECT VehicleID, Description, 'Non-Applicable'
                        FROM VEHICLE
                        WHERE VehicleID NOT IN (SELECT VehicleID FROM RENTAL))
                        WHERE Description LIKE ?
                        GROUP BY VehicleID
                        ''', ('%' + description2.get() + '%',))
    
    output_records = iq_cur.fetchall()

    print_record = ''

    for output_record in output_records:
        print_record += str(output_record[0]) + " " + str(output_record[1]) + " " + str(output_record[2]) + "\n"
    
    listbox.delete(0, END)
    for line in print_record.split('\n'):
        listbox.insert(END, line)
	
	#commit changes

    iq_conn.commit()
	#close the DB connection
    iq_conn.close()

#building the gui components
	# pack place grid

	# create text boxes


title_label = Label(root, text = 'Car Rental Database', font=('Arial', 28, "bold"), fg='#ffffff', bg='#0064B1')
title_label.grid(row = 0, column = 0, sticky=EW, columnspan=8, padx=0)

# -------------ADD CUSTOMER----------------
ac_label = Label(root, text = 'Add Customer...', font=('Arial 12 bold underline'), fg='#ffffff', bg='#0064B1')
ac_label.grid(row = 1, column = 0)

name_label = Label(root, text = 'Name: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
name_label.grid(row = 2, column = 0)
name = Entry(root, width = 30, bd=0)
name.grid(row = 2, column = 1, padx = 20)

phone_label = Label(root, text = 'Phone: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
phone_label.grid(row = 3, column = 0)
phone = Entry(root, width = 30)
phone.grid(row = 3, column = 1)

submit_cust_btn = Button(root, text ='Add Customer ', command = submitCustomer, fg='#ffffff', bg='#F58025', bd=0, width=5, font="Arial 16 bold")
submit_cust_btn.grid(row = 9, column =0, columnspan = 2, pady = 10, padx = 10, ipadx = 140)


# ------------ADD VEHICLE--------------
# VehicleID, :Description, :Year, :Category, :Type
av_label = Label(root, text = 'Add Vehicle...', font=('Arial 12 bold underline'), fg='#ffffff', bg='#0064B1')
av_label.grid(row = 1, column = 3)

vehicleid_label = Label(root, text = 'VehicleID: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
vehicleid_label.grid(row = 2, column = 3)
vehicleid = Entry(root, width = 30)
vehicleid.grid(row = 2, column = 4)

description_label = Label(root, text = 'Description: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
description_label.grid(row = 3, column = 3)
description = Entry(root, width = 30)
description.grid(row = 3, column = 4)

year_label = Label(root, text = 'Year: ', height=1, fg='#ffffff', bg='#0064B1', font="Arial 12")
year_label.grid(row = 4, column = 3)
year = Entry(root, width = 30)
year.grid(row = 4, column = 4)

category_label = Label(root, text = 'Category: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
category_label.grid(row = 5, column = 3)
category = Entry(root, width = 30)
category.grid(row = 5, column = 4)

cartype_label = Label(root, text = 'Type: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
cartype_label.grid(row = 6, column = 3)
cartype = Entry(root, width = 30)
cartype.grid(row = 6, column = 4)

submit_vehicle_btn = Button(root, text ='Add Vehicle ', command = submitVehicle, fg='#ffffff', bg='#F58025', bd=0, width=5, font="Arial 16 bold")
submit_vehicle_btn.grid(row = 9, column = 3, columnspan = 2, pady = 10, padx = 10, ipadx = 140)


# -------------- ADD RENTAL ------------------
#custid, cartype2, category2, startdate, returndate, rentaltype, qty, paymentdate
ar_label = Label(root, text = 'Add Rental...', font=('Arial 12 bold underline'), fg='#ffffff', bg='#0064B1')
ar_label.grid(row = 10, column = 0)

custid_label = Label(root, text = 'CustID: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
custid_label.grid(row = 11, column = 0, )
custid = Entry(root, width = 30)
custid.grid(row = 11, column = 1)

cartype2_label = Label(root, text = 'Car Type: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
cartype2_label.grid(row = 12, column = 0)
cartype2 = Entry(root, width = 30)
cartype2.grid(row = 12, column = 1)

category2_label = Label(root, text = 'Category: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
category2_label.grid(row = 13, column = 0)
category2 = Entry(root, width = 30)
category2.grid(row = 13, column = 1)

startdate_label = Label(root, text = 'Start Date: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
startdate_label.grid(row = 13, column = 0)
startdate = Entry(root, width = 30)
startdate.grid(row = 13, column = 1)

returndate_label = Label(root, text = 'Return Date: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
returndate_label.grid(row = 14, column = 0)
returndate = Entry(root, width = 30)
returndate.grid(row = 14, column = 1)

rentaltype_label = Label(root, text = 'Rental Type: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
rentaltype_label.grid(row = 15, column = 0)
rentaltype = Entry(root, width = 30)
rentaltype.grid(row = 15, column = 1)

qty_label = Label(root, text = 'Quantity: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
qty_label.grid(row = 16, column = 0)
qty = Entry(root, width = 30)
qty.grid(row = 16, column = 1)

paymentdate_label = Label(root, text = 'Payment Date: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
paymentdate_label.grid(row = 17, column = 0)
paymentdate = Entry(root, width = 30)
paymentdate.grid(row = 17, column = 1)

submit_rental_btn = Button(root, text ='Add Rental ', command = submitRental, fg='#ffffff', bg='#F58025', bd=0, width=5, font="Arial 16 bold")
submit_rental_btn.grid(row = 18, column =0, columnspan = 2, pady = 10, padx = 10, ipadx = 140)


# -------------- PAY RENTAL ------------------
pr_label = Label(root, text = 'Pay Rental...', font=('Arial 12 bold underline'), fg='#ffffff', bg='#0064B1')
pr_label.grid(row = 10, column = 3)

name2_label = Label(root, text = 'Name: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
name2_label.grid(row = 11, column = 3)
name2 = Entry(root, width = 30)
name2.grid(row = 11, column = 4)

vehicleid3_label = Label(root, text = 'Vehicle ID: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
vehicleid3_label.grid(row = 12, column = 3)
vehicleid3 = Entry(root, width = 30)
vehicleid3.grid(row = 12, column = 4)

returndate2_label = Label(root, text = 'Return Date: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
returndate2_label.grid(row = 13, column = 3)
returndate2 = Entry(root, width = 30)
returndate2.grid(row = 13, column = 4)

return_rental_qry_btn = Button(root, text = 'Pay Rental', command = return_rental_query, fg='#ffffff', bg='#F58025', bd=0, width=5, font="Arial 16 bold")
return_rental_qry_btn.grid(row = 18, column = 3, columnspan = 2, pady = 10, padx = 10, ipadx = 140)


# ------------- SEARCH BALANCES ------------------
sb_label = Label(root, text = 'Search Balances...', font=('Arial 12 bold underline'), fg='#ffffff', bg='#0064B1')
sb_label.grid(row = 19, column = 0)

custid2_label = Label(root, text = 'Customer ID: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
custid2_label.grid(row = 20, column = 0)
custid2 = Entry(root, width = 30)
custid2.grid(row = 20, column = 1)

name3_label = Label(root, text = 'Name: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
name3_label.grid(row = 21, column = 0)
name3 = Entry(root, width = 30)
name3.grid(row = 21, column = 1)

cust_balance_qry_btn = Button(root, text = 'Search balances', command = customer_balance_query, fg='#ffffff', bg='#F58025', bd=0, width=5, font="Arial 16 bold")
cust_balance_qry_btn.grid(row = 23, column = 0, columnspan = 2, pady = 10, padx = 10, ipadx = 140)

# ------------ SEARCH VEHICLES ----------------
sv_label = Label(root, text = 'Search Vehicles...', font=('Arial 12 bold underline'), fg='#ffffff', bg='#0064B1')
sv_label.grid(row = 19, column = 3)

vehicleid4_label = Label(root, text = 'Vehicle ID: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
vehicleid4_label.grid(row = 20, column = 3)
vehicleid4 = Entry(root, width = 30)
vehicleid4.grid(row = 20, column = 4)

description_label2 = Label(root, text = 'Description: ', fg='#ffffff', bg='#0064B1', font="Arial 12")
description_label2.grid(row = 21, column = 3)
description2 = Entry(root, width = 30)
description2.grid(row = 21, column = 4)

vehicle_qry_btn = Button(root, text = 'Search vehicles', command = vehicle_rate_query, fg='#ffffff', bg='#F58025', bd=0, width=5, font="Arial 16 bold")
vehicle_qry_btn.grid(row = 23, column = 3, columnspan = 2, pady = 10, padx = 10, ipadx = 140)
#----------------------------
listbox.grid(row=24, column=0, columnspan=8)

#executes tinker components
root.mainloop()

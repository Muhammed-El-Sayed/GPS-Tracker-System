
# import gmplot package
import gmplot

longitude_list_test = []
latitude_list_test = []
file = open("hello.txt","r")
for line in file :
    fiels = line.split(" ")
    longitude_list_test.append(fiels[0])
    latitude_list_test.append(fiels[1])

print(longitude_list_test)
print(latitude_list_test)

longitude_list_test_float = []
latitude_list_test_float = []
for item in longitude_list_test:
    longitude_list_test_float.append(float(item))

for item in latitude_list_test:
    latitude_list_test_float.append(float(item))

    
longitude_list = [ 31.28448, 31.28274, 31.28159, 31.28010, 31.27922, 31.27833, 31.27629, 31.27406 ]
latitude_list = [ 30.07327, 30.07140, 30.07024, 30.06875, 30.06791, 30.06698, 30.06529,30.06450  ]

gmap3 = gmplot.GoogleMapPlotter(30.07327,
                                31.28448, 15)
  
# scatter method of map object 
# scatter points on the google map
gmap3.scatter( latitude_list_test, longitude_list_test , '#FF0000',
                              size = 40, marker = False )
  
# Plot method Draw a line in
# between given coordinates
gmap3.plot(latitude_list_test_float, longitude_list_test_float, 
           'cornflowerblue', edge_width = 2.5)
gmap3.draw( "C:\\Users\\ZAMALA\\Desktop\\map13.html" )

# import gmplot package
import gmplot

longitude_list_test = []
latitude_list_test = []
file = open("hello.txt","r")
for line in file :
    fiels = line.split(",")    #15.46512,13.46162 ##
    longitude_list_test.append(fiels[0])
    x = fiels[1].split(" ")
    latitude_list_test.append(x[0])

print(longitude_list_test)
print(latitude_list_test)

longitude_list_test_float = []
latitude_list_test_float = []
for item in longitude_list_test:
    longitude_list_test_float.append(float(item))

for item in latitude_list_test:
    latitude_list_test_float.append(float(item))

    

gmap3 = gmplot.GoogleMapPlotter(longitude_list_test[0],  latitude_list_test[0], 25)

#gmap3 = gmplot.GoogleMapPlotter(30.07327,
 #                               31.28448, 15)
# scatter method of map object 
# scatter points on the google map
gmap3.scatter( longitude_list_test_float, latitude_list_test_float, '#FF0000',
                              size = 2, marker = False )
  
# Plot method Draw a line in
# between given coordinates
gmap3.plot(longitude_list_test_float, latitude_list_test_float,
           'cornflowerblue', edge_width = 2.5)
gmap3.draw( "C:\\Users\\g.version\\Desktop\\map13.html" )
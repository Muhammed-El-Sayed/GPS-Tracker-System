//
//  ViewController.swift
//  GPS tracker app
//
//  Created by Mohamed Khalid on 02/06/2021.
//

import UIKit
import MapKit

class MainViewController: UIViewController {
    var gpsManager = GPSServiceManager.shared
    var coreDataManager = CoreDataService()
    
    var currentTrajectory = [PossitionModel]()
    var distance = 0.0
    var sourceCoordinates: CLLocationCoordinate2D?
    var destinationCoordinates: CLLocationCoordinate2D?
    
    // TEST POSSITIONS
    //    var possitions = [
    //        PossitionModel(latitude: 90.4657, longitude: 31.83635),
    //        PossitionModel(latitude: 80.123, longitude: 94.91235)
    //    ]
    
    @IBOutlet weak var mapView: MKMapView?
    @IBOutlet weak var showSavedTrajectoriesButton: UIButton!
    @IBOutlet weak var showGPSReadingsButton: UIButton!
    @IBOutlet weak var saveButton: UIButton!
    @IBOutlet weak var reloadButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        gpsManager.delegate = self
        
        //        let sourceLocation = CLLocationCoordinate2D(latitude: 30.1234, longitude: 31.1234)
        //        let destinationLocation = CLLocationCoordinate2D(latitude: 30.432, longitude: 31.453)
        //        createPath(sourceLocation: sourceLocation, destinationLocation: destinationLocation)
        
        if let safeMapView = mapView {
            safeMapView.delegate = self
            safeMapView.clearsContextBeforeDrawing = true
        }
        // Initial Possition 
        //        currentTrajectory = [//30.171577317969167, 31.427694745214676
        //            PossitionModel(latitude: 30.06674 , longitude: 31.27810),
        //            PossitionModel(latitude: 30.06559, longitude: 31.27695 ),
        //            PossitionModel(latitude: 30.06512, longitude: 31.27602)
        //            PossitionModel(latitude: 31.430613, longitude: 30.170705)
        //        ]
        
        
        
        
        saveButton.layer.cornerRadius = saveButton.frame.size.height / 2
        saveButton.layer.borderWidth = 1
        saveButton.layer.borderColor = UIColor.white.cgColor
        showGPSReadingsButton.layer.cornerRadius = showGPSReadingsButton.frame.size.height / 2
        showGPSReadingsButton.layer.borderWidth = 1
        showGPSReadingsButton.layer.borderColor = UIColor.white.cgColor
        showSavedTrajectoriesButton.layer.cornerRadius = showSavedTrajectoriesButton.frame.size.height / 2
        showSavedTrajectoriesButton.layer.borderWidth = 1
        showSavedTrajectoriesButton.layer.borderColor = UIColor.white.cgColor
        reloadButton.layer.cornerRadius = reloadButton.frame.size.height / 2
        reloadButton.layer.borderWidth = 1
        reloadButton.layer.borderColor = UIColor.white.cgColor
        
    }
    
    
    func createPath(sourceLocation : CLLocationCoordinate2D, destinationLocation : CLLocationCoordinate2D) {
        let sourcePlaceMark = MKPlacemark(coordinate: sourceLocation, addressDictionary: nil)
        let destinationPlaceMark = MKPlacemark(coordinate: destinationLocation, addressDictionary: nil)
        
        
        let sourceMapItem = MKMapItem(placemark: sourcePlaceMark)
        let destinationItem = MKMapItem(placemark: destinationPlaceMark)
        
        
        
        
        
        
        
        let directionRequest = MKDirections.Request()
        directionRequest.source = sourceMapItem
        directionRequest.destination = destinationItem
        directionRequest.transportType = .automobile
        
        let direction = MKDirections(request: directionRequest)
        
        
        direction.calculate { (response, error) in
            guard let response = response else {
                if let error = error {
                    print("ERROR FOUND: \(error.localizedDescription)")
                }
                return
            }
            
            let route = response.routes[0]
            if let safeMapView = self.mapView {
                safeMapView.addOverlay(route.polyline, level: MKOverlayLevel.aboveRoads)
                
                let rect = route.polyline.boundingMapRect
                
                safeMapView.setRegion(MKCoordinateRegion(rect), animated: true)
            }
        }
    }
    
    func calculateDistance() -> Double {
        // MARK:- Implement distance calculator function
        return 0.0
    }
    func drawTrajectory() {
        DispatchQueue.main.async {
            self.mapView?.clearsContextBeforeDrawing = true
            if (self.currentTrajectory.count >= 2) {

                self.sourceCoordinates = CLLocationCoordinate2D(latitude: self.currentTrajectory.first!.latitude, longitude: self.currentTrajectory.first!.longitude)
                self.destinationCoordinates = CLLocationCoordinate2D(latitude: self.currentTrajectory.last!.latitude, longitude: self.currentTrajectory.last!.longitude)
                let sourceAnotation = MKPointAnnotation()
                sourceAnotation.title = "Source"
                sourceAnotation.coordinate = self.sourceCoordinates!
                let destinationAnotation = MKPointAnnotation()
                destinationAnotation.title = "Destination"
                destinationAnotation.coordinate = self.destinationCoordinates!

                if let safeMapView = self.mapView {
                    let annotations = safeMapView.annotations
                    safeMapView.removeAnnotations(annotations)
                    safeMapView.addAnnotation(sourceAnotation)
                    safeMapView.addAnnotation(destinationAnotation)
                }
                
                
                
                print("Can create a path.")
                for i in 0..<(self.currentTrajectory.count - 1) {
                    let sourceLocation = CLLocationCoordinate2D(latitude: self.currentTrajectory[i].latitude, longitude: self.currentTrajectory[i].longitude)
                    let destinationLocation = CLLocationCoordinate2D(latitude: self.currentTrajectory[i+1].latitude, longitude: self.currentTrajectory[i+1].longitude)
                    self.createPath(sourceLocation: sourceLocation, destinationLocation: destinationLocation)
                }
            }
        }
      
    }
    
    @IBAction func reloadButtonPressed(_ sender: Any) {
        gpsManager.delegate = self
        currentTrajectory.removeAll()
        gpsManager.fetchPossitions()
        print("Got possitions")
    }
    
    @IBAction func saveButtonPressed(_ sender: Any) {
        print("Count in current trajectory = \(currentTrajectory.count)")
        if(currentTrajectory.count < 2) {
            print("ALEEEERT saving")
            let alert = UIAlertController(title: "Error", message: "Cannot save the trajectory because number of sent data < 2 possitions", preferredStyle: .alert)
            let action = UIAlertAction(title: "OK", style: .cancel, handler: nil)
            alert.addAction(action)
            dismiss(animated: true){ () -> Void in
                self.present(alert, animated: true, completion: nil)}
        } else {
            coreDataManager.insert(sourceLatitude: currentTrajectory.first!.latitude, sourceLongitude: currentTrajectory.first!.longitude, destinationLatitude: currentTrajectory.last!.latitude, destinationLongitude: currentTrajectory.last!.longitude, distance: calculateDistance())
        }
    }
}

extension MainViewController : MKMapViewDelegate {
    func mapView(_ mapView: MKMapView, rendererFor overlay: MKOverlay) -> MKOverlayRenderer {
        let rendere = MKPolylineRenderer(overlay: overlay)
        rendere.lineWidth = 5
        rendere.strokeColor = .systemBlue
        
        return rendere
    }
}

extension MainViewController: GPSServiceManagerDelegate {
    func didUpdatePossition(_ gpsServiceManager: GPSServiceManager, possitions: [PossitionModel]) {
        currentTrajectory.removeAll()
        //        DispatchQueue.main.async {
        if (possitions.count >= 2) {
            self.currentTrajectory = possitions
            print ("CurrentTrajectory count : ")
            print(self.currentTrajectory.count)
            if (self.currentTrajectory.count >= 2) {
                print("Can create a path.")
                for i in 0..<(self.currentTrajectory.count - 1) {
                    let sourceLocation = CLLocationCoordinate2D(latitude: self.currentTrajectory[i].latitude, longitude: self.currentTrajectory[i].longitude)
                    let destinationLocation = CLLocationCoordinate2D(latitude: self.currentTrajectory[i+1].latitude, longitude: self.currentTrajectory[i+1].longitude)
                    self.createPath(sourceLocation: sourceLocation, destinationLocation: destinationLocation)
                    self.drawTrajectory()
                }
            }
        }
        else {
            DispatchQueue.main.async {
                let alert = UIAlertController(title: "Error", message: "Cannot draw the trajectory because number of sent data < 2", preferredStyle: .alert)
                let action = UIAlertAction(title: "OK", style: .cancel, handler: nil)
                alert.addAction(action)
                self.dismiss(animated: true){ () -> Void in
                    self.present(alert, animated: true, completion: nil)
                }
            }
        }
        
        //        }
        
    }
    
    func didFailWithError(_ gpsServiceManager: GPSServiceManager, error: Error) {
        print(error)
    }
    
    
}

extension MainViewController { //Prepaiting for segues
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "Go_To_Saved_Trajectories" {
            let destinationVC = segue.destination as! SavedTrajectoriesViewController
            gpsManager.delegate = destinationVC.self
            destinationVC.savedTrajectories = coreDataManager.fetch()
            print("number of data sent = \(destinationVC.savedTrajectories?.count)")
        }
        else if segue.identifier == "Go_To_Possitions" {
            print ("Going to possition VC")
            let detinationVC = segue.destination as! PossitionsLogViewController
            gpsManager.delegate = detinationVC.self
            gpsManager.fetchPossitions()
            
        }
    }
}


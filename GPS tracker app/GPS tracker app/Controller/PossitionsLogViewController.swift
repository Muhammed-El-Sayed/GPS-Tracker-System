//
//  PossitionsLogViewController.swift
//  GPS tracker app
//
//  Created by Mohamed Khalid on 03/06/2021.
//

import UIKit

class PossitionsLogViewController: UIViewController {

    
    var possitions: [PossitionModel]?
    var gpsManager = GPSServiceManager.shared

    
    @IBOutlet weak var possitionsTableView: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        possitionsTableView.delegate = self
        possitionsTableView.dataSource = self
        
        // Test data
//        possitions = [
//            PossitionModel(latitude: 1.1, longitude: 1.2),
//            PossitionModel(latitude: 2.1, longitude: 2.2),
//            PossitionModel(latitude: 3.1, longitude: 3.2)
//        ]
        //possitionsTableView.reloadData()
  //      gpsManager.fetchPossition()
    }
    

}


extension PossitionsLogViewController: GPSServiceManagerDelegate {
    
    func didUpdatePossition(_ gpsServiceManager: GPSServiceManager, possitions: [PossitionModel]) {
        self.possitions = possitions
        print("equaling")
        DispatchQueue.main.async {
            print("In main thread")
            self.possitionsTableView.reloadData()
        }
    }
    
    func didFailWithError(_ gpsServiceManager: GPSServiceManager, error: Error) {
        print(error)
    }
}

extension PossitionsLogViewController: UITableViewDelegate, UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return possitions?.count ?? 0
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = possitionsTableView.dequeueReusableCell(withIdentifier: "Possitions_Cell", for: indexPath) as! PossitionTableViewCell
        if let safePossitions = possitions {
            cell.longitudeLabel.text = String(safePossitions[indexPath.row].longitude)
            cell.latitudeLabel.text = String(safePossitions[indexPath.row].latitude)
        }
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        possitionsTableView.cellForRow(at: indexPath)?.setSelected(false, animated: true)
    }
}

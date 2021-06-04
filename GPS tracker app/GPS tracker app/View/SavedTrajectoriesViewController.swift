//
//  SavedTrajectoriesViewController.swift
//  GPS tracker app
//
//  Created by Mohamed Khalid on 03/06/2021.
//

import UIKit

class SavedTrajectoriesViewController: UIViewController {

    var gpsManager = GPSServiceManager.shared
    var savedTrajectories: [Trajectory]?
    var coreDataManager = CoreDataService()

    
    @IBOutlet weak var savedTrajectoriesTableView: UITableView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        savedTrajectoriesTableView.delegate = self
        savedTrajectoriesTableView.dataSource = self
        print("Number of data received = \(savedTrajectories?.count)")
    }

    @IBAction func trashButtonPressed(_ sender: Any) {
        coreDataManager.deleteAll()
        savedTrajectories?.removeAll()
        savedTrajectoriesTableView.reloadData()
    }
}


extension SavedTrajectoriesViewController: UITableViewDelegate, UITableViewDataSource{
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return savedTrajectories?.count ?? 0
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = savedTrajectoriesTableView.dequeueReusableCell(withIdentifier: "Saved_Trajectories_Cell", for: indexPath) as? SavedTrajectoriesTableViewCell
        if let safeSaveData = savedTrajectories {
            let dateFormatter = DateFormatter()
            if let safeCell = cell {
                //print("Entered ")
                
                let dateFormatterGet = DateFormatter()
                dateFormatterGet.dateFormat = "yyyy-MM-dd HH:mm:ss"
            
                safeCell.dateLabel.text = ("Date: \( dateFormatterGet.string(from: safeSaveData[indexPath.row].saveDate!))")
                safeCell.destinationLatitudeLabel.text = ("     Latitude: \(safeSaveData[indexPath.row].destinationLatitude)")
                safeCell.destinationLongitudeLabel.text = ("     Longitude: \(safeSaveData[indexPath.row].destinationLongitude)")
                safeCell.sourceLatitudeLabel.text = String("     Latitude: \(safeSaveData[indexPath.row].sourceLatitude)")
                safeCell.sourceLongitudeLabel.text = ("     Longitude: \(String(safeSaveData[indexPath.row].sourceLongitude))")
                return safeCell
            }
        }
        return UITableViewCell()
    }
}

extension SavedTrajectoriesViewController: GPSServiceManagerDelegate {
    func didUpdatePossition(_ gpsServiceManager: GPSServiceManager, possitions: [PossitionModel]) {
        DispatchQueue.main.async {
            print("Number of data received \(self.savedTrajectories?.count)")
            self.savedTrajectoriesTableView.reloadData()
        }
    }
    
    func didFailWithError(_ gpsServiceManager: GPSServiceManager, error: Error) {
        print(error)
    }
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        savedTrajectoriesTableView.cellForRow(at: indexPath)?.setSelected(false, animated: true)
    }
}



//
//  CoreDataService.swift
//  GPS tracker app
//
//  Created by Mohamed Khalid on 03/06/2021.
//

import UIKit
import CoreData

// Responsible for dealing with CoreData
//
struct CoreDataService {
    var savedElements: [Trajectory]?
    let context = (UIApplication.shared.delegate as! AppDelegate).persistentContainer.viewContext
    let backgroundContext = (UIApplication.shared.delegate as! AppDelegate).backgroundContext
    
    init() {
        backgroundContext.performAndWait {
            savedElements = fetch()
        }
    }

    mutating func insert(sourceLatitude: Double, sourceLongitude: Double, destinationLatitude: Double, destinationLongitude: Double, distance: Double) {
        print("entered inserting function")
            let trajectory = Trajectory(context: backgroundContext)
            trajectory.sourceLatitude = sourceLatitude
            trajectory.sourceLongitude = sourceLongitude
            trajectory.destinationLatitude = destinationLatitude
            trajectory.destinationLongitude = destinationLongitude
            trajectory.distance = distance
            trajectory.saveDate = Date()
        print("start inserting \(trajectory.saveDate)")
            backgroundContext.insert(trajectory)
            print("inserted")
            savedElements?.append(trajectory)
            checkStorageLimit()
        print(savedElements?.count)
    }
    
    mutating func fetch() -> [Trajectory]?{
        backgroundContext.performAndWait {
            let fetchRequest:NSFetchRequest<Trajectory> = Trajectory.fetchRequest()
            do {
                savedElements = try backgroundContext.fetch(fetchRequest)
            } catch {
                print(error)
            }
        }
        return savedElements
    }
    
    mutating func deleteAll() {
        let fetchRequest: NSFetchRequest<NSFetchRequestResult> = Trajectory.fetchRequest()
        let batchDeleteRequest = NSBatchDeleteRequest(fetchRequest: fetchRequest)
        do {
            try backgroundContext.execute(batchDeleteRequest)
        } catch {
            print(error)
        }
    }
    
    // Ensures that saved items doesn't exceed 1000 element
    //
    mutating func checkStorageLimit() {
        backgroundContext.performAndWait {
            if var elements = savedElements {
                if (elements.count > 1000) {
                    deleteEarliestElement(&elements)
                }
            }
            do {
                try backgroundContext.save()
            } catch  {
                print(error)
            }
        }
    }
    
    mutating func deleteEarliestElement(_ elements: inout [Trajectory]) {
        backgroundContext.performAndWait {
            // Sort the elements array in order to execute the function in o(sort) rather than o(n^2)
            elements.sort {
                $0.saveDate ?? Date() > $1.saveDate ?? Date()
            }
            // Deleting in o(1)
            backgroundContext.delete(elements.last!)
            elements.removeLast()
        }
    }
}

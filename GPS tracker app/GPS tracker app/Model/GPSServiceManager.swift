//
//  GPSServiceManager.swift
//  GPS tracker app
//
//  Created by Mohamed Khalid on 03/06/2021.
//

import Foundation

protocol GPSServiceManagerDelegate {
    func didUpdatePossition(_ gpsServiceManager: GPSServiceManager, possitions: [PossitionModel])
    func didFailWithError(_ gpsServiceManager: GPSServiceManager, error: Error)
}

struct GPSServiceManager {
    static let shared = GPSServiceManager()

    let GPSDataURL = "https://script.googleusercontent.com/macros/echo?user_content_key=a9NRuyPyA2FyvatIs84L_isj7CuQE7eaSnS3F_HQKb8pkan-b98vr4q2hFqamvkBPnIJ4tUUAKpe6X-o3wW_y9o3aN_6rO8fm5_BxDlH2jW0nuo2oDemN9CCS2h10ox_1xSncGQajx_ryfhECjZEnHFjDCwzSB4Px5ZkrLeZl-Uge2ZAneyelEWd5FoID2_bwr3T-Ja00N9qCxOpr9FwPFQDMoY5k8guXJIRhmMHxXrl0-G--jLB-A&lib=MAw8bVJEpNq-d9upNF_u8AZXv_sM7Qa-L"
    var delegate: GPSServiceManagerDelegate?
    
    func fetchPossitions() {
        // Make any edits to the URL
        // let urlString = ""
        requestPossition()
    }
    
    func requestPossition(){
        print("Requesting")
        // 1. Create URL
        guard let url = URL(string: GPSDataURL) else { return }
        // 2. Create URLSession
        let session = URLSession(configuration: .default)
        // 3. Give task to URL
        let task = session.dataTask(with: url) {(data, response, error) in
            if let safeData = data {
                if let possitions = parseJSON(safeData){
                    print("Will update")
                    delegate?.didUpdatePossition(self, possitions: possitions)
                    print(" updated")

                }
                if let safeError = error{
                    delegate?.didFailWithError(self, error: safeError)
                }
            }
        }
        // 4. Start task
        task.resume()
    }

    func parseJSON (_ jsonData: Data) -> [PossitionModel]?{
        let decoder = JSONDecoder()
        do{
            let gpsData = try decoder.decode(GPSData.self, from: jsonData)
            var possition: [PossitionModel]?
            if let safeFeeds = gpsData.feeds {
                print (safeFeeds.count)
                possition = [PossitionModel]()
                for feed in safeFeeds {
                    let longitude = Double(feed.field1)
                    let latitude = Double(feed.field2)
//                    if let safeLongitude = longitude, let safeLatitude = latitude {
                        possition?.append(PossitionModel(latitude: latitude, longitude: longitude))
//                    }
                }
            }
            return possition
        } catch {
            delegate?.didFailWithError(self, error: error)
            return nil
        }
    }

    
    
    
}

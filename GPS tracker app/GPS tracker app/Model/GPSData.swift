//
//  Possition.swift
//  GPS tracker app
//
//  Created by Mohamed Khalid on 03/06/2021.
//

import Foundation

struct GPSData: Decodable{
    let channel: Channel?
    let feeds: [Feed]?
}

struct Channel: Decodable{
    let latitude: String
    let longitude: String
}

struct Feed: Decodable {
    let entry_id: Int
    let field1: String
    let field2: String
}

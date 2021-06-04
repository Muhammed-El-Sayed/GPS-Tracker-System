//
//  SavedTrajectoriesTableViewCell.swift
//  GPS tracker app
//
//  Created by Mohamed Khalid on 04/06/2021.
//

import UIKit

class SavedTrajectoriesTableViewCell: UITableViewCell {

    
    @IBOutlet weak var dateLabel: UILabel!
    @IBOutlet weak var sourceLongitudeLabel: UILabel!
    @IBOutlet weak var sourceLatitudeLabel: UILabel!
    @IBOutlet weak var destinationLongitudeLabel: UILabel!
    @IBOutlet weak var destinationLatitudeLabel: UILabel!
    @IBOutlet weak var distanceLabel: UILabel!
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}



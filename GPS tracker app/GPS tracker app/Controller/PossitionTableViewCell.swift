//
//  PossitionTableViewCell.swift
//  GPS tracker app
//
//  Created by Mohamed Khalid on 03/06/2021.
//

import UIKit

class PossitionTableViewCell: UITableViewCell {

    @IBOutlet weak var longitudeLabel: UILabel!
    @IBOutlet weak var latitudeLabel: UILabel!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

    }

}

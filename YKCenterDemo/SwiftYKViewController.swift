//
//  SwiftYKViewController.swift
//  YKCenterDemo
//
//  Created by Don on 2017/6/9.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

import UIKit

class SwiftYKViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        let loginVC = YKLoginViewController()
        loginVC.userLogin(true);
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}

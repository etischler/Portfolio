//
//  ViewController.swift
//  Odds?!
//
//  Created by Edward Tischler on 6/27/16.
//  Copyright © 2016 Edward Tischler. All rights reserved.
//
//import FBSDKLoginKit
import UIKit

class ViewController: UIViewController, FBSDKLoginButtonDelegate {
    @IBOutlet weak var ChallengeButtonOutlet: UIButton!
    @IBOutlet weak var PendingChallengesOutlet: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        if (FBSDKAccessToken.currentAccessToken() != nil)
        {
            // User is already logged in, do work such as go to next view controller.
            print("user already loggin in")
        }
        else{
            //performSegueWithIdentifier("toLoginPage", sender: self)
            
            let loginView : FBSDKLoginButton = FBSDKLoginButton()
            loginView.loginBehavior = FBSDKLoginBehavior.Web
            self.view.addSubview(loginView)
            loginView.center = self.view.center
            loginView.readPermissions = ["public_profile", "email", "user_friends"]
            loginView.delegate = self
            ChallengeButtonOutlet.hidden = true
            PendingChallengesOutlet.hidden = true
            
            
        }
    }
    func loginButton(loginButton: FBSDKLoginButton!, didCompleteWithResult result: FBSDKLoginManagerLoginResult!, error: NSError!) {
        print("User Logged In")
        
        if ((error) != nil)
        {
            // Process error
        }
        else if result.isCancelled {
            // Handle cancellations
            print("cancelled")
        }
        else {
            // If you ask for multiple permissions at once, you
            // should check if specific permissions missing
            if result.grantedPermissions.contains("email")
            {
                // Do work
            }
        }
    }
    func loginButtonDidLogOut(loginButton: FBSDKLoginButton!) {
        
        
        print("User Logged Out")
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}


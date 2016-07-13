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
    let loginView : FBSDKLoginButton = FBSDKLoginButton()
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        if (FBSDKAccessToken.currentAccessToken() != nil)
        {
            // User is already logged in, do work such as go to next view controller.
            print("user already loggin in")
            //GET RID OF THE FOLLOWING BLOCK FOR PRODUCTION
            
            loginView.loginBehavior = FBSDKLoginBehavior.Web
            self.view.addSubview(loginView)
            loginView.center = self.view.center
            loginView.readPermissions = ["public_profile", "email", "user_friends"]
            loginView.delegate = self
            ChallengeButtonOutlet.hidden = false
            PendingChallengesOutlet.hidden = false
            
            //END OF BLOCK
        }
        else{
            //performSegueWithIdentifier("toLoginPage", sender: self)
            print(loginView.frame.size)
            loginView.frame.size = CGSizeMake(253.5, 45);
            
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
        else {//MAKE SURE TO ADD ID****
            // If you ask for multiple permissions at once, you
            // should check if specific permissions missing
            if result.grantedPermissions.contains("email")
            {
                ChallengeButtonOutlet.hidden = false;
                PendingChallengesOutlet.hidden = false;
                loginView.hidden = true;
                
                returnUserData()
                // Do work
            }
        }
    }
    func loginButtonDidLogOut(loginButton: FBSDKLoginButton!) {
        
        
        print("User Logged Out")
    }
    
    func returnUserData()
    {
        let graphRequest : FBSDKGraphRequest = FBSDKGraphRequest(graphPath:"me", parameters: ["fields":"email,name,id"])
        graphRequest.startWithCompletionHandler({ (connection, result, error) -> Void in
            
            if ((error) != nil)
            {
                // Process error
                print("Error: \(error)")
            }
            else
            {
                print("fetched user: \(result)")
                let userName : NSString = result.valueForKey("name") as! NSString
                //print("User Name is: \(userName)")
                let userEmail : NSString = result.valueForKey("email") as! NSString
                //print("User Email is: \(userEmail)")
                let userId : NSString = result.valueForKey("id") as! NSString
                //print("User ID is: \(userId)")
                
                let alert = UIAlertController(title: "Welcome!", message: ("Hello " + (userName as String) + ", we at Odds noticed you are a new user and would like to say thanks for joining! Don't know how to play? Sure! Under 'Challenge a Friend', be sure to chose the bot and we will walk you through your first game! Have fun and happy daring!"), preferredStyle: UIAlertControllerStyle.Alert)
                alert.addAction(UIAlertAction(title: "Done", style: UIAlertActionStyle.Default, handler: nil))
                self.presentViewController(alert, animated: true, completion: nil)
                
                
                
                
            }
        })
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
	

}


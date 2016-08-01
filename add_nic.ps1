clear
$netName = Read-Host 'Provide me the name of the network please. For example : xx.xxx.xx.x/xx'
echo "Please wait while I query"
echo ""
$VMs = Get-VM | where {$_.NetworkAdapters.NetworkName -eq $netName}
echo "These will be the VMs that receive a new nic:"
echo $VMs.Name
echo ""
$proceed = Read-Host 'Proceed? (y/n)'
if($proceed -eq 'y'){
    echo "Proceeding..."
    echo ""
    foreach($VM in $VMs){
        Get-VM $VM.Name | New-NetworkAdapter  -NetworkName $netName -StartConnected -Type VMXNET3
        echo ""
        echo "$VM has received a nic"
        echo ""
        #Read-Host 'Proceed? (y/n)'
    }
}
else{
echo "User aborted."
}



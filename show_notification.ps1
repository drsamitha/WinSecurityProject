# Import the BurntToast module
Import-Module BurntToast

# Create "Yes" and "No" buttonss
$YesButton = New-BTButton -Content 'Yes' -Arguments 'Yes'
$NoButton = New-BTButton -Content 'No' -Arguments 'No'

# Display a toast notification with the buttons
New-BurntToastNotification -Text 'File modified', 'Do you want to take any action?' -Button $YesButton, $NoButton

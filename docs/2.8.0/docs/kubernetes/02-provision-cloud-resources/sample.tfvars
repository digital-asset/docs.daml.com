### Mandatory variables

# Target Azure location
# https://azure.microsoft.com/explore/global-infrastructure/geographies/#geographies
# az account list-locations --output table
location = ""

# Name prefix for all resources that will be created
name_prefix = ""

# Existing Azure Resource Group where all resources will be created
resource_group_name = ""

# Local path to SSH private key to access bastion, supported formats:
# https://learn.microsoft.com/en-us/azure/virtual-machines/linux/mac-create-ssh-keys
# The SSH public key should also exist (i.e. /path/to/ssh/key.pub)
bastion_ssh_key_path = "/path/to/ssh/key"

# Custom private DNS, should be different from existing public DNS' to avoid conflicts
private_dns_zone_name = "private.zero.k8s"

# Default Canton participant name used in this guide
jwt_audience_suffix = "participant1"

#
# Given a log file. Find the uniq ips.
#

cat inputs/uniq_ip.log | awk '{print $1}' | uniq

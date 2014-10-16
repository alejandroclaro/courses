# buyLotsOfFruit.py
# -----------------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

fruitPrices = {'apples':2.00, 'oranges': 1.50, 'pears': 1.75, 'limes':0.75, 'strawberries':1.00}

def buyLotsOfFruit(orderList):
    totalCost = 0.0             
    
    # ASSIGNMENT ##########################################

    for fruit, pound in orderList:

        if fruit not in fruitPrices:
            print "Sorry we don't have %s" % (fruit)
            return None
        else:
            totalCost += fruitPrices[fruit] * pound
		
    # ASSIGNMENT ##########################################
	
    return totalCost
    
# Main Method    
if __name__ == '__main__':
    "This code runs when you invoke the script from the command line"
    orderList = [ ('apples', 2.0), ('pears', 3.0), ('limes', 4.0) ]
    print 'Cost of', orderList, 'is', buyLotsOfFruit(orderList)
### NOTE: you may need to install some packages as you go. If your program is not running, it
### may mean that you don't have a certain package to do it. 
install.packages("mlbench")
install.packages('car')
library(mlbench)
# list the contents of the library
#library(help = "mlbench")
library("ggplot2")                     # Load ggplot2 package
library("GGally")                      # Load GGally package
library(lmtest)
library(corrplot)
library(car)


# 1. Make sure that you place your dataset in the same folder where the R file is saved
# 2. Go to Session-> Set Working Directory-> To Source File Location
# 3. Read in your data. On the right hand side window click and check your data
data=read.csv('df2.csv')
# 4. You will notice that an extra column was created for the index, we need to remove it
df = subset(data, select = -c(X) )
# you can always look at your data either going to the right upper window, 
# or calling the head() function
head(df)

# 5. Let's run our full regression model. We only have to specify our "y", the "~." takes care
# all the other variables. No need to change fuel_type to dummy
model1=lm(price~., data=df)

#Alternatively you could use
model1b=lm(price~fuel_type+wheel_base+length+width+heights+curb_weight+engine_size+bore+stroke+comprassion+horse_power+peak_rpm+city_mpg+highway_mpg, data=df)


# 6. To see the results use the command bellow
summary(model1)
summary(model1b)


######################################################
####### WHAT YOU SHOULD DO ##########################

# Create a new dataframe called df_new that only contains the significant variables
# Look at the marks at the end of each row. Hint: you should keep only 8 variables.
# Create a new regression model (call it model2) with only the significant variables.

model2->
  
# OR you can just type in the significant variables like in model1b, in which case you 
# don't need to create a new dataframe

model2b->

# Compare your models with ANOVA. What do you find?
#If you used the alternative ways, make sure that you change the model names in the function
anova(model2, model1)
#Check to see that the order of the models does not matter for the results
anova(model1, model2)

# Check for multicollinearity
vif(model1)
vif(model2)

#Assumptions( you have to click enter a couple of times to see the graphs in the lower right window)
plot(model1)

#Check to see if your assumptions validity improved
plot(model2)

ggpairs(df)


##### Variable selection ########
library(MASS)

# Stepwise regression models
############################
# backward-forward selection
step.model_both <- step(model1, direction = "both", 
                      trace = FALSE)
summary(step.model_both)

# forward selection
step.model_forward <- step(model1, direction = "forward", 
                        trace = FALSE)
summary(step.model_forward)

#backward selection
step.model_backward <- step(model1, direction = "backward", 
                        trace = FALSE)
summary(step.model_backward)

###You can look up the code for regularized regressions. It is pretty straight forward as well

from os import write
import yfinance as yf
import numpy as nf
from datetime import datetime
import csv
stock = yf.Ticker("NVDA")
history = stock.history(period="1y")
returns = history['Close'].pct_change().dropna()
spot = history['Close'].iloc[-1]
volatility = returns.std()*(252**0.5)
risk_rate = 0.038
exp = stock.options[2]
end_date=datetime.strptime(exp,"%Y-%m-%d")
days=(end_date-datetime.now()).days
expiry = days/365
call_option = stock.option_chain(exp)
call = call_option.calls[['strike','lastPrice']]
 
with open('data_inputs.csv', 'w', newline='') as f:
      writer = csv.writer(f)
      writer.writerow(['ticker', 'spot', 'volatility', 'rate', 'expiry'])
      writer.writerow([stock, spot, volatility, risk_rate, expiry])

call.to_csv('call_info.csv', index=False)

print(f"Ticker :{stock}")
print(f"Spot :{spot}")
print(f"Volatility :{volatility}")
print(f"Risk-Free Rate :{risk_rate}")
print(f"Expiry :{expiry}")
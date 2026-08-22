from os import write
import yfinance as yf
import numpy as nf
import csv
stock = yf.Ticker("NVDA")
history = stock.history(period="1y")
returns = history['Close'].pct_change().dropna()
spot = history['Close'].iloc[-1]
volatility = returns.std()*(252**0.5)
risk_rate = 0.038
exp = stock.options[0]
call_option = stock.option_chain(exp)
call = call_option.calls[['strike','lastPrice']]
 
with open('data_inputs.csv', 'w', newline='') as f:
      writer = csv.writer(f)
      writer.writerow(['ticker', 'spot', 'volatility', 'rate', 'expiry'])
      writer.writerow([stock, spot, returns, risk_rate, exp])

call.to_csv('call_info.csv', index=False)

print(f"Ticker :{stock}")
print(f"Spot :{spot}")
print(f"Volatility :{volatility}")
print(f"Risk-Free Rate :{risk_rate}")
print(f"Expiry :{exp}")
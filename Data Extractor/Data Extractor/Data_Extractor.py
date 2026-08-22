import yfinance as yf
import numpy as nf
stock = yf.Ticker("NVDA")
history = stock.history(period="1y")
returns = history['Close'].pct_change().dropna()
spot = history['Close'].iloc[-1]
volatility = returns.std()*(252**0.5)
exp = stock.options[0]
call_option = stock.option_chain(exp)
print(call_option)


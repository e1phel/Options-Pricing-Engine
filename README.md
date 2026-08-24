# Options Pricing Engine (C++ + Real Market Data)

An object-oriented C++ pricing engine that implements the Black-Scholes model, prices real NVDA call options, and compares the theoretical price against live market data pulled from Yahoo Finance.

## What this does

Given real market inputs — current stock price, historical volatility, risk-free rate, and time to expiry — this program computes the theoretical "fair value" of a call option using the Black-Scholes formula, then checks that against the option's actual last-traded market price. It also computes Delta, the option's sensitivity to the underlying stock price.

The ticker is configurable — swapping the stock symbol in the data-fetching script lets you pull data and run this same engine for a different company. Note that the strike range selected out of the option chain is currently tuned around NVDA's price level, so results are cleanest for similarly priced, liquid stocks without further adjustment.

### Tickers

| Ticker | Company |
|---|---|
| NVDA | Nvidia |
| AAPL | Apple |
| MSFT | Microsoft |
| GOOGL | Alphabet (Google) |
| AMZN | Amazon |
| TSLA | Tesla |
| META | Meta |

## Concepts demonstrated

- **Object-Oriented Design**: encapsulation of market data, inheritance between the data-loading and pricing classes, and a clean separation between data loading and pricing logic
- **Black-Scholes Option Pricing Model**: the standardized probability terms and the standard normal cumulative distribution function, implemented from scratch
- **Delta (Greeks)**: computed analytically, showing how option sensitivity changes across strikes
- **Real-world data pipeline**: a script fetches live spot price, annualized historical volatility, and real option chain data, which is then consumed by the pricing engine

## How it works

A data-fetching script connects to a market data provider, pulls a year of daily NVDA prices, computes annualized historical volatility from daily returns, and grabs the real option chain for a chosen expiry date. This is written out to two data files: one holding the market-wide inputs (spot, volatility, rate, expiry), and one holding the option chain (strike, market price).

The pricing engine reads both files, builds a pricing object per strike, and runs each through the Black-Scholes formula.

The output table shows, for each strike: the theoretical price, the real market price, the difference between them, and Delta.

## Sample Output

<img width="727" height="390" alt="image" src="https://github.com/user-attachments/assets/c6e33fde-608e-47ac-b21e-192eba839239" />

## Findings

- Delta decreases smoothly as strike increases (0.99 → 0.93), consistent with Black-Scholes theory — options further from being deep in-the-money become progressively less sensitive to the stock price. When tested against even deeper in-the-money strikes (well below spot), Delta saturates at 1.00, since the standard normal cumulative distribution function converges to 1 once its input gets large enough.
- The theoretical price consistently undershoots the market price across every strike tested (average difference: $1.97). This is likely because the model's volatility input is based on trailing historical volatility, while the market's real premium may be pricing in additional near-term uncertainty (e.g. upcoming earnings) — a real-world gap between historical and implied volatility.

## Known Limitations

1. Assumes constant volatility (Black-Scholes' key simplifying assumption) — real markets exhibit a "volatility smile," where implied volatility varies by strike
2. Uses historical volatility rather than market-implied volatility, which contributes to the systematic pricing gap observed above
3. Assumes no dividends and European-style exercise (no early exercise)
4. Risk-free rate is a fixed approximation based on current short-term Treasury yields, not matched precisely to the option's exact expiry

import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash[0]["cash"]
    stocks = db.execute("SELECT * FROM portfolio WHERE user_id = (?)", user_id)
    grandtotal = cash
    for stock in stocks:
        grandtotal += stock["total"]

    return render_template(
        "index.html", stocks=stocks, cash=cash, grandtotal=grandtotal
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not lookup(request.form.get("symbol")):
            return apology("ivalid symbol")

        try:
            int(request.form.get("shares"))
        except ValueError:
            return apology("invalid shares")

        if int(request.form.get("shares")) < 1:
            return apology("invalid shares")

        elif lookup(request.form.get("symbol")):
            symbol = request.form.get("symbol")
            symbol = lookup(symbol)["symbol"]
            name = lookup(symbol)["name"]
            price = lookup(symbol)["price"]
            shares = int(request.form.get("shares"))
            user_id = session["user_id"]

            cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
            cash = cash[0]["cash"]

            if cash < (price * shares):
                return apology("can't afford")
            else:
                cash -= price * shares
                db.execute(
                    "INSERT INTO history (user_id, symbol, shares, price) VALUES ( ?, ?, ?, ?)",
                    user_id,
                    symbol,
                    shares,
                    price,
                )
                db.execute("UPDATE users SET cash = (?) WHERE id = (?)", cash, user_id)

                rows = db.execute(
                    "SELECT * FROM portfolio WHERE user_id = (?) AND symbol = (?)",
                    user_id,
                    symbol,
                )
                if len(rows) != 1:
                    total = price * shares
                    db.execute(
                        "INSERT INTO portfolio (user_id, symbol, name, shares, price, total) VALUES ( ?, ?, ?, ?, ?, ?)",
                        user_id,
                        symbol,
                        name,
                        shares,
                        price,
                        total,
                    )
                else:
                    shares_old = db.execute(
                        "SELECT shares FROM portfolio WHERE user_id = (?) AND symbol = (?)",
                        user_id,
                        symbol,
                    )
                    shares += shares_old[0]["shares"]
                    total = price * shares
                    db.execute(
                        "UPDATE portfolio SET shares = ?, price = ?, total = ? WHERE user_id = ? AND symbol = ?",
                        shares,
                        price,
                        total,
                        user_id,
                        symbol,
                    )

                return index()

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM history WHERE user_id = (?)", user_id)
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if lookup(request.form.get("symbol")):
            symbol = request.form.get("symbol")
            symbol = lookup(symbol)["symbol"]
            name = lookup(symbol)["name"]
            price = lookup(symbol)["price"]
            return render_template("quoted.html", symbol=symbol, name=name, price=price)
        else:
            return apology("ivalid symbol")
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif request.form.get("username"):
            # Query database for username
            rows = db.execute(
                "SELECT * FROM users WHERE username = ?", request.form.get("username")
            )

            # Ensure username does not exist yet
            if len(rows) > 0:
                return apology("username already exists", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        if request.form.get("confirmation") != request.form.get("password"):
            return apology("passwords do not match", 400)

        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES ( ?, ?)", username, hash)
        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":
        if not lookup(request.form.get("symbol")):
            return apology("ivalid symbol")

        symbol = request.form.get("symbol")
        symbol = lookup(symbol)["symbol"]

        rows = db.execute(
            "SELECT * FROM portfolio WHERE user_id = (?) AND symbol = (?)",
            user_id,
            symbol,
        )
        if len(rows) != 1:
            return apology("ivalid symbol")

        try:
            int(request.form.get("shares"))
        except ValueError:
            return apology("invalid shares")

        shares = int(request.form.get("shares"))
        portshares = db.execute(
            "SELECT shares FROM portfolio WHERE user_id = (?) AND symbol = (?)",
            user_id,
            symbol,
        )
        portshares = portshares[0]["shares"]
        if shares < 1 or shares > portshares:
            return apology("invalid shares")

        else:
            shares *= -1
            price = lookup(symbol)["price"]
            cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
            cash = cash[0]["cash"]
            cash -= price * shares

            db.execute(
                "INSERT INTO history (user_id, symbol, shares, price) VALUES ( ?, ?, ?, ?)",
                user_id,
                symbol,
                shares,
                price,
            )
            db.execute("UPDATE users SET cash = (?) WHERE id = (?)", cash, user_id)

            portshares += shares
            if portshares > 0:
                total = price * shares
                db.execute(
                    "UPDATE portfolio SET shares = ?, price = ?, total = ? WHERE user_id = ? AND symbol = ?",
                    portshares,
                    price,
                    total,
                    user_id,
                    symbol,
                )
            else:
                db.execute("DELETE FROM portfolio WHERE symbol = ?", symbol)

            return index()

    else:
        stocks = db.execute("SELECT * FROM portfolio WHERE user_id = (?)", user_id)
        print(stocks)
        return render_template("sell.html", stocks=stocks)


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash[0]["cash"]

    if request.method == "POST":
        try:
            int(request.form.get("addcash"))
        except ValueError:
            return apology("invalid amount")

        if int(request.form.get("addcash")) < 1:
            return apology("invalid amount")

        cash += int(request.form.get("addcash"))
        db.execute("UPDATE users SET cash = (?) WHERE id = (?)", cash, user_id)

        return render_template("addcash.html", cash=cash)
    else:
        return render_template("addcash.html", cash=cash)
